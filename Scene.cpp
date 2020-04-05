#include <vector>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <ctime>
#include <omp.h>
#include <limits>

#include "mygeometry.h"

constexpr double GlobalLightning = 0.2;

static unsigned int normalisePixel(double pixel) {
    return (unsigned int) (255 * std::max(0.0, std::min(1.0, pixel)));
}

std::vector<unsigned int>
vPixel2Ui(const std::vector<Pixel> &frame, const int width, const int height) {
    std::vector<unsigned int> frameUi(frame.size());
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            Pixel curPixel = frame[i * width + j];
            double maxV = std::max(std::max(curPixel[0], curPixel[1]), curPixel[2]);
            if (maxV > 1) {
                curPixel = curPixel * (1.0 / maxV);
            }
            frameUi[(height - i - 1) * width + j] = (normalisePixel(curPixel[0])) |
                                                    (normalisePixel(curPixel[1]) << 8) |
                                                    (normalisePixel(curPixel[2]) << 16);
        }
    }
    return frameUi;
}

bool
objectIntersect(const Point &orig, const Point &dir, const std::vector<BasicObject *> &objects, Point &hit, Point &N,
                Material &material) {
    double spheres_dist = MAX_DIST + 1;
    for (const auto &object : objects) {
        double dist_i;
        if (object->areIntersected(orig, dir, dist_i) && dist_i < spheres_dist) {
            spheres_dist = dist_i;
            hit = orig + dir * dist_i;
            N = object->getNormal(hit);
            material = object->getMaterial(hit);
        }
    }
    return spheres_dist < MAX_DIST;
}

Point calcRefract(const Point &V, const Point &N, const double refIdx) {
    // Snell's law
    double cos = -std::max(-1.0, std::min(1.0, V * N));
    double n1 = 1;
    double n2 = refIdx;
    Point n = N;
    if (cos < 0) {
        cos *= -1;
        std::swap(n1, n2);
        n = n * -1;
    }
    double d = n1 / n2;
    double k = 1.1 - d * d * (1 - cos * cos);
    if (k < 0) {
        return Point();
    }
    return V * d + n * (d * cos - sqrt(k));
}

Pixel
cast_ray(const Point &orig, const Point &dir, const std::vector<BasicObject *> &objects,
         const std::vector<Light> &lights, int refLevel = 1) {
    Point point, N;
    Material material;
    if (refComplexity < refLevel || !objectIntersect(orig, dir, objects, point, N, material)) {
        return Colour(0.1, 0.05, 0.1);
    }

    Point reflectDirection = dir.reflect(N);
    Point reflectOrigin = point + (N * (reflectDirection * N)).normalized() * EPS;

    Point refractDirection = calcRefract(dir, N, material.refractiveIndex).normalize();
    Point refractOrigin = point + (N * (refractDirection * N)).normalized() * EPS;

    ReflectionParams reflectionParams = cast_ray(reflectOrigin, reflectDirection, objects, lights, refLevel + 1);
    RefractionParams refractionParams = cast_ray(refractOrigin, refractDirection, objects, lights, refLevel + 1);

    double lightDiffIntensity = 0, lightSpecIntensity = 0;
    for (const auto &light : lights) {
        Point lightDirection = (light.getPosition() - point).normalized();

        double lightDist = (light.getPosition() - point).length();
        Point shadowOrigin = point + (N * (lightDirection * N)).normalized() * EPS;
        Point shadowP, shadowNormal;
        Material tempMaterial;
        bool intersect = objectIntersect(shadowOrigin, lightDirection, objects, shadowP, shadowNormal, tempMaterial);
        if (intersect && (shadowP - shadowOrigin).length() < lightDist) {
            continue;
        }
        lightDiffIntensity += light.getIntensity() * std::max(0., lightDirection * N);
        lightSpecIntensity +=
                pow(std::max(0.0, lightDirection.reflect(N) * dir), material.specularParam) * light.getIntensity();
    }
    return material.diffusiveParams * (lightDiffIntensity + GlobalLightning) * material.reflectionParams[0] +
           Pixel(1.0, 1.0, 1.0) * lightSpecIntensity * material.reflectionParams[1] +
           reflectionParams * material.reflectionParams[2] + refractionParams * material.refractiveParam;
}

std::vector<unsigned int>
scene(const std::vector<BasicObject *> &objects, const std::vector<Light> &lights, const int height, const int width,
      int threads) {
    omp_set_num_threads(threads);

    const double fov = M_PI / 3.0;
    std::vector<Pixel> framebuffer(width * height);

    for (size_t j = 0; j < height; j++) {
        std::cout << "\rGenerated: " << (j + 1.0) / height * 100 << "%" << std::flush;

#pragma omp parallel for
        for (size_t i = 0; i < width; i++) {
            double x = (2 * i / (double) width - 1) * tan(fov / 2.0) * width / (double) height;
            double y = -(2 * j / (double) height - 1) * tan(fov / 2.0);
            Point dir = Point(x, y, -1);
            framebuffer[i + j * width] = cast_ray(Point(0, 0, 0), dir.normalize(), objects, lights, 1);
        }
    }
    std::cout << std::endl;

    return vPixel2Ui(framebuffer, width, height);
}
