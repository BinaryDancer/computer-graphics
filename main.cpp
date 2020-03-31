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

    if (sceneId != 4) {
        uint32_t color = 0;
        if (sceneId == 1)
            color = RED;
        else if (sceneId == 2)
            color = RED | GREEN;
        else if (sceneId == 3)
            color = BLUE;

        std::vector<uint32_t> image(512 * 512);
        for (auto &pixel : image)
            pixel = color;

        SaveBMP(outFilePath.c_str(), image.data(), 512, 512);
    } else {
        Material      ivory({0.6,  0.3}, Vec3d(0.4, 0.4, 0.3),   50.);
        Material red_rubber({0.9,  0.1}, Vec3d(0.3, 0.1, 0.1),   10.);

        std::vector<Sphere> spheres;
        spheres.push_back(Sphere(Vec3d(-3,    0,   -16), 3,      ivory));
        spheres.push_back(Sphere(Vec3d(-2, -1.5, -12), 3, red_rubber));
        spheres.push_back(Sphere(Vec3d( 3, -1, -18), 4, red_rubber));
        spheres.push_back(Sphere(Vec3d( 10,    10,   -18), 6,      ivory));

        std::vector<Light>  lights;
        lights.push_back(Light(Vec3d(20, 20,  20), 2));
        lights.push_back(Light(Vec3d( 30, 50, -25), 1.8));
        lights.push_back(Light(Vec3d( 30, 20,  30), 1.7));
        render(spheres, lights);
    }
    std::cout << "end." << std::endl;
    return 0;
}