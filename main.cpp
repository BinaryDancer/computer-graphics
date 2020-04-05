#include <iostream>
#include <cstdint>

#include <string>
#include <vector>
#include <unordered_map>

#include "Bitmap.h"
#include "Scene.h"

const uint32_t RED = 0x000000FF;
const uint32_t GREEN = 0x0000FF00;
const uint32_t BLUE = 0x00FF0000;

int main(int argc, const char **argv) {
    std::unordered_map<std::string, std::string> cmdLineParams;

    for (int i = 0; i < argc; i++) {
        std::string key(argv[i]);

        if (key.size() > 0 && key[0] == '-') {
            if (i != argc - 1) // not last argument
            {
                cmdLineParams[key] = argv[i + 1];
                i++;
            } else
                cmdLineParams[key] = "";
        }
    }

    std::string outFilePath = "zout.bmp";
    if (cmdLineParams.find("-out") != cmdLineParams.end())
        outFilePath = cmdLineParams["-out"];

    int sceneId = 1;
    if (cmdLineParams.find("-scene") != cmdLineParams.end())
        sceneId = atoi(cmdLineParams["-scene"].c_str());

    int threads = 1;
    if (cmdLineParams.find("-threads") != cmdLineParams.end())
        threads = atoi(cmdLineParams["-threads"].c_str());

    int height = 600;
    int width = 600;
    std::vector<unsigned int> image;
    if (sceneId == 1) {
        // planes
        Material gray_polished(ReflectionParams(0.5, 0.3, 0.1), DiffusiveParams(0.3, 0.4, 0.4), 45.0, 0.0, 1.0);
        Material pink_polished(ReflectionParams(0.5, 0.3, 0.1), DiffusiveParams(0.5, 0.2, 0.5), 45.0, 0.0, 1.0);
        Material green_polished(ReflectionParams(0.5, 0.3, 0.1), DiffusiveParams(0.3, 0.5, 0.3), 45.0, 0.0, 1.0);
        Material red_polished(ReflectionParams(0.5, 0.3, 0.1), DiffusiveParams(0.5, 0.2, 0.2), 45.0, 0.0, 1.0);
        Material yellow_polished(ReflectionParams(0.5, 0.3, 0.1), DiffusiveParams(0.7, 0.5, 0.0), 45.0, 0.0, 1.0);
        Material pastel_matte_plane(ReflectionParams(0.8, 0.2, 0.0), DiffusiveParams(0.4, 0.4, 0.3), 10.0, 0.0, 1.0);
        Material blue_matte(ReflectionParams(0.9, 0.1, 0.0), DiffusiveParams(0.1, 0.1, 0.3), 10.0, 0.0, 1.0);
        Material dark_glass(ReflectionParams(0.0, 0.5, 0.1), DiffusiveParams(0.5, 0.6, 0.7), 125., 0.8, 1.5);

        std::vector<BasicObject *> objects;
        Sphere sp1 = Sphere(Point(-4, -4, -16), 3, gray_polished);
        objects.push_back(&sp1);
        Sphere sp2 = Sphere(Point(4, -4, -14), 2.5, green_polished);
        objects.push_back(&sp2);

        Sphere sp3 = Sphere(Point(-1, -1, -11), 2, dark_glass);
        objects.push_back(&sp3);
        Sphere sp4 = Sphere(Point(1.5, -0.5, -30), 4, pink_polished);
        objects.push_back(&sp4);
        Sphere sp5 = Sphere(Point(8, -6, -24), 6, red_polished);
        objects.push_back(&sp5);
        Sphere sp6 = Sphere(Point(-10, 2, -24), 4, yellow_polished);
        objects.push_back(&sp6);

        Plane plane = Plane(Point(0.0, -7.0, 0.0), Point(0.0, 1.0, 0.0), blue_matte, pastel_matte_plane);
        objects.push_back(&plane);

        std::vector<Light> lights;
        lights.emplace_back(Point(-5, 4, -7.5), 1.8);
        lights.emplace_back(Point(5, 4, -7.5), 1.8);

        image = scene(objects, lights, width, height, threads);
    } else if (sceneId == 2) {
        // room
        Material gray_polished(ReflectionParams(0.5, 0.3, 0.1), DiffusiveParams(0.3, 0.4, 0.4), 45.0, 0.0, 1.0);
        Material purple_matte_wall(ReflectionParams(0.8, 0.2, 0.0), DiffusiveParams(0.3, 0.3, 0.4), 10.0, 0.0, 1.0);
        Material pastel_matte_wall(ReflectionParams(0.8, 0.2, 0.0), DiffusiveParams(0.4, 0.4, 0.3), 10.0, 0.0, 1.0);
        Material red_matte_wall(ReflectionParams(0.8, 0.2, 0.0), DiffusiveParams(0.6, 0.1, 0.1), 10.0, 0.0, 1.0);
        Material dark_red_matte(ReflectionParams(0.8, 0.2, 0.0), DiffusiveParams(0.3, 0.1, 0.1), 10.0, 0.0, 1.0);
        Material blue_matte(ReflectionParams(0.9, 0.1, 0.0), DiffusiveParams(0.1, 0.1, 0.3), 10.0, 0.0, 1.0);
        Material mirror(ReflectionParams(0.0, 10.0, 0.9), DiffusiveParams(1.0, 1.0, 1.0), 1400.0, 0.0, 1.0);

        std::vector<BasicObject *> objects;
        Sphere sp1 = Sphere(Point(-3.99, -3.99, -15.99), 3, gray_polished);
        objects.push_back(&sp1);
        Sphere sp2 = Sphere(Point(4, -4.49, -13.99), 2.5, mirror);
        objects.push_back(&sp2);

        Plane floor = Plane(Point(0.0, -7.0, 0.0), Point(0.0, 1.0, 0.0), blue_matte, pastel_matte_wall);
        objects.push_back(&floor);
        Plane up = Plane(Point(0.0, 7.0, 0.0), Point(0.0, -1.0, 0.0), dark_red_matte, dark_red_matte);
        objects.push_back(&up);
        Plane left = Plane(Point(-7.0, 0.0, 0.0), Point(1.0, 0.0, 0.0), purple_matte_wall, purple_matte_wall);
        objects.push_back(&left);
        Plane right = Plane(Point(7.0, 0.0, 0.0), Point(-1.0, 0.0, 0.0), purple_matte_wall, purple_matte_wall);
        objects.push_back(&right);
        Plane back = Plane(Point(0.0, 0.0, -20.0), Point(0.0, 0.0, 1.0), purple_matte_wall, purple_matte_wall);
        objects.push_back(&back);
        Plane front = Plane(Point(0.0, 0.0, 5.0), Point(0.0, 0.0, -1.0), purple_matte_wall, red_matte_wall);
        objects.push_back(&front);

        Triangle wall_mir1 = Triangle(Point(-3.0, 0.0, -19.99999), Point(3.0, 0.0, -19.99999),
                                      Point(3.0, 5.0, -19.99999),
                                      mirror);
        Triangle wall_mir2 = Triangle(Point(-3.0, 5.0, -19.99999), Point(-3.0, 0.0, -19.99999),
                                      Point(3.0, 5.0, -19.99999),
                                      mirror);
        Triangle floor_triangle1 = Triangle(Point(-3.0, -7.0, -20.0), Point(0.0, -7.0, -17.0), Point(0.0, -3.0, -20.0),
                                            red_matte_wall);
        Triangle floor_triangle2 = Triangle(Point(3.0, -7.0, -20.0), Point(0.0, -3.0, -20.0), Point(0.0, -7.0, -17.0),
                                            red_matte_wall);
        objects.push_back(&floor_triangle1);
        objects.push_back(&floor_triangle2);
        objects.push_back(&wall_mir1);
        objects.push_back(&wall_mir2);

        std::vector<Light> lights;
        lights.emplace_back(Point(-5, 4, -10), 1.8);
        lights.emplace_back(Point(5, 4, -10), 1.8);

        image = scene(objects, lights, width, height, threads);
    } else {
        return 0;
    }

    SaveBMP(outFilePath.c_str(), image.data(), width, height);
    std::cout << "end." << std::endl;
    return 0;
}