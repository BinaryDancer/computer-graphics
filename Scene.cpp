#include <vector>
#include <cstdlib>
#include <cmath>

#include "Bitmap.h"
#include "mygeometry.h"

static unsigned int normalise(double p) {

}

unsigned int *vPixel2Ui(const std::vector<Pixel> &frame, int width, int height) {
    auto frameUi = new unsigned int[frame.size()];
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            Vec3f &c = framebuffer[i];
            float max = std::max(c[0], std::max(c[1], c[2]));
            if (max>1) c = c*(1./max);

                ofs << (char)(255 * std::max(0.f, std::min(1.f, framebuffer[i][j])));
            }
            frameUi[(height - i - 1) * width + j] = ((unsigned int) (255 * frame[i * width + j][0]) << 16) |
                                                    ((unsigned int) (255 * frame[i * width + j][1]) << 8) |
                                                    ((unsigned int) (255 * frame[i * width + j][2]));
        }
    }
    return frameUi;
}

bool scene_intersect(const Vec3d &orig, const Vec3d &dir, const std::vector<Sphere> &spheres, Vec3d &hit, Vec3d &N,
                     Material &material) {
    double spheres_dist = std::numeric_limits<float>::max();
    for (size_t i = 0; i < spheres.size(); i++) {
        double dist_i;
        if (spheres[i].areIntersected(orig, dir, dist_i) && dist_i < spheres_dist) {
            spheres_dist = dist_i;
            hit = orig + dir * dist_i;
            N = (hit - spheres[i].getCenter()).normalize();
            material.diffuse_colour = spheres[i].getColour();
        }
    }
    return spheres_dist < 1000;
}

Pixel
cast_ray(const Vec3d &orig, const Vec3d &dir, const std::vector<Sphere> &spheres, const std::vector<Light> &lights) {
    Vec3d point, N;
    Material material;

    if (!scene_intersect(orig, dir, spheres, point, N, material)) {
        return Pixel(0.2, 0.7, 0.8); // background color
    }

    double diffuse_light_intensity = 0;
    double specular_light_intensity = 0;
    for (size_t i = 0; i < lights.size(); ++i) {
        Vec3d light_dir = (lights[i].getPosition() - point).normalize();
        diffuse_light_intensity += lights[i].getIntensity() * std::max(0., light_dir * N);
        specular_light_intensity +=
                powf(std::max(0.0, light_dir.reflect(N) * dir), material.specular_param) * lights[i].getIntensity();
    }
    return material.diffuse_colour * diffuse_light_intensity * material.ambient_params.first +
           Vec3d(1.0, 1.0, 1.0) * specular_light_intensity * material.ambient_params.second;
}

void render(const std::vector<Sphere> &spheres, const std::vector<Light> &lights) {
    const int width = 1024;
    const int height = 1024;
    const double fov = M_PI / 2;
    std::vector<Pixel> framebuffer(width * height);

    for (size_t j = 0; j < height; j++) {
        for (size_t i = 0; i < width; i++) {
            double x = (2 * (i + 0.5) / (double) width - 1) * tan(fov / 2.) * width / (double) height;
            double y = -(2 * (j + 0.5) / (double) height - 1) * tan(fov / 2.);
            Vec3d dir = Vec3d(x, y, -1).normalize();
            framebuffer[i + j * width] = cast_ray(Vec3d(0, 0, 0), dir, spheres, lights);
        }
    }

    auto frameUi = vPixel2Ui(framebuffer, width, height);
    SaveBMP("test1.bmp", frameUi, width, height);
}
