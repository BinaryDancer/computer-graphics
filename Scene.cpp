#include <vector>
#include <cstdlib>
#include <cmath>

#include "mygeometry.h"

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

bool spheres_intersect(const Point &orig, const Point &dir, const std::vector<Sphere> &spheres, Point &hit, Point &N,
                       Material &material, double &minDist) {
    double spheres_dist = std::numeric_limits<double>::max();
    for (const auto &sphere : spheres) {
        double dist_i;
        if (sphere.areIntersected(orig, dir, dist_i) && dist_i < spheres_dist) {
            spheres_dist = dist_i;
            hit = orig + dir * dist_i;
            N = (hit - sphere.getCenter()).normalize();
            material = sphere.getMaterial();
        }
    }

    minDist = spheres_dist;

    return spheres_dist < MAX_DIST;
}

bool planes_intersect(const Point &orig, const Point &dir, const std::vector<Plane> &planes, Point &hit, Point &N,
                      Material &material, double &minDist) {
    double plane_dist = minDist;
    for (const auto &plane : planes) {
        double dist_i;
        if (plane.areIntersected(orig, dir, dist_i) && dist_i < plane_dist) {
            plane_dist = dist_i;
            hit = orig + dir * dist_i;
            N = plane.getNormal();
            material = plane.getMaterial(hit);

        }
    }

    minDist = plane_dist;
    return plane_dist < MAX_DIST;
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
cast_ray(const Point &orig, const Point &dir, const std::vector<Sphere> &spheres, const std::vector<Light> &lights,
         int refLevel = 1, const std::vector<Plane> &planes = {}) {
    Point point, N;
    Material material;
    double minDist = MAX_DIST + 1;
    volatile bool int1 = spheres_intersect(orig, dir, spheres, point, N, material, minDist);
    volatile bool int2 = planes_intersect(orig, dir, planes, point, N, material, minDist);
    volatile bool intF = int1 || int2;
    if (refComplexity < refLevel || !intF) {
        return Colour(0.2, 0.7, 0.8);
    }

    Point reflect_dir = dir.reflect(N);
    Point reflect_orig = point + (N * (reflect_dir * N)).normalized() * EPS;

    Point refract_dir = calcRefract(dir, N, material.refractiveIndex).normalize();
    Point refract_orig = point + (N * (refract_dir * N)).normalized() * EPS;

    ReflectionParams reflectionParams = cast_ray(reflect_orig, reflect_dir, spheres, lights, refLevel + 1, planes);
    RefractionParams refractionParams = cast_ray(refract_orig, refract_dir, spheres, lights, refLevel + 1, planes);

    double diffuse_light_intensity = 0;
    double specular_light_intensity = 0;
    for (const auto &light : lights) {
        Point light_dir = (light.getPosition() - point).normalized();

        // shadows
        double light_distance = (light.getPosition() - point).length();
        Point shadow_orig = point + (N * (light_dir * N)).normalized() * EPS;
        Point shadow_pt, shadow_N;
        Material tempMaterial;
        double tempMinDist = MAX_DIST + 1;
        bool intersect = spheres_intersect(shadow_orig, light_dir, spheres, shadow_pt, shadow_N, tempMaterial, tempMinDist);
        if (intersect && (shadow_pt - shadow_orig).length() < light_distance)
            continue;

        diffuse_light_intensity += light.getIntensity() * std::max(0., light_dir * N);
        specular_light_intensity +=
                pow(std::max(0.0, light_dir.reflect(N) * dir), material.specularParam) * light.getIntensity();
    }
    return material.diffusiveParams * diffuse_light_intensity * material.reflectionParams[0] +
           Pixel(1.0, 1.0, 1.0) * specular_light_intensity * material.reflectionParams[1] +
           reflectionParams * material.reflectionParams[2] + refractionParams * material.refractiveParam;
}

std::vector<unsigned int>
scene1(const std::vector<Sphere> &spheres, const std::vector<Light> &lights, const std::vector<Plane> &planes,
       const int height, const int width) {
    const double fov = M_PI / 3.0;
    std::vector<Pixel> framebuffer(width * height);

    for (size_t j = 0; j < height; j++) {
        for (size_t i = 0; i < width; i++) {
            double x = (2 * i / (double) width - 1) * tan(fov / 2.0) * width / (double) height;
            double y = -(2 * j / (double) height - 1) * tan(fov / 2.0);
            Point dir = Point(x, y, -1);
            framebuffer[i + j * width] = cast_ray(Point(0, 0, 0), dir.normalize(), spheres, lights, 1, planes);
        }
    }

    return vPixel2Ui(framebuffer, width, height);
}
