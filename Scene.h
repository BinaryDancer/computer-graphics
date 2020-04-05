#ifndef RT_SCENE_H
#define RT_SCENE_H

#include "mygeometry.h"

std::vector<unsigned int>
scene(const std::vector<BasicObject*> &objects, const std::vector<Light> &lights, const int height, const int width, int threads);

#endif //RT_SCENE_H
