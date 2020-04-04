#ifndef RT_SCENE_H
#define RT_SCENE_H

#include "mygeometry.h"

std::vector<unsigned int> scene1(const std::vector<Sphere> &spheres, const std::vector<Light> &lights, const std::vector<Plane> &planes, const int height, const int width);

#endif //RT_SCENE_H
