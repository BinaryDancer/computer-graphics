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

    int sceneId = 0;
    if (cmdLineParams.find("-scene") != cmdLineParams.end())
        sceneId = atoi(cmdLineParams["-scene"].c_str());

    uint32_t color = 0;
    int height = 600;
    int width = 600;
    std::vector<unsigned int> image;
    if (sceneId == 1) {
        Material ivory(ReflectionParams(0.6, 0.3, 0.1), DiffusiveParams(0.4, 0.4, 0.3), 50.0, 0.0, 1.0);
        Material red_rubber(ReflectionParams(0.9, 0.1, 0.0), DiffusiveParams(0.3, 0.1, 0.1), 10.0, 0.0, 1.0);
        Material black_rubber(ReflectionParams(0.0, 0.0, 0.0), DiffusiveParams(0.1, 0.1, 0.1), 1.0, 0.0, 1.0);
        Material mirror(ReflectionParams(0.0, 10.0, 0.8), DiffusiveParams(1.0, 1.0, 1.0), 1425.0, 0.0, 1.0);
        Material glass(ReflectionParams(0.0, 0.5, 0.1), DiffusiveParams(0.6, 0.7, 0.8), 125., 0.8, 1.5);

        std::vector<Sphere> spheres;
        spheres.emplace_back(Point(-3, 0, -16), 2, ivory);
        spheres.emplace_back(Point(-1, -1.5, -12), 2, glass);
        spheres.emplace_back(Point(1.5, -0.5, -30), 3, red_rubber);
        spheres.emplace_back(Point(7, 5, -18), 4, mirror);

        std::vector<Plane> planes;
        planes.emplace_back(Plane(Point(0.0, -4.0, 0.0), Point(0.0, 1.0, 0.0), black_rubber, ivory));
//        planes.emplace_back(Plane(Point(0.0, 51.0, 0.0), Point(0.0, -1.0, 0.0), ivory, black_rubber));
//        planes.emplace_back(Plane(Point(0.0, 0.0, -60.0), Point(0.0, 0.0, 1.0), ivory, ivory));


        std::vector<Light> lights;
        lights.emplace_back(Point(-20, 20, 20), 1.5);
        lights.emplace_back(Point(30, 50, -25), 1.8);
        lights.emplace_back(Point(30, 20, 30), 1.7);

        image = scene1(spheres, lights, planes, width, height);
    } else if (sceneId == 2)
        color = RED | GREEN;
    else if (sceneId == 3)
        color = BLUE;

    SaveBMP(outFilePath.c_str(), image.data(), width, height);
    std::cout << "end." << std::endl;
    return 0;
}