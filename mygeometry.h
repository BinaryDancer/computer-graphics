//
// Created by Павел Мамаев on 28.03.2020.
//

#ifndef RT_MYGEOMETRY_H
#define RT_MYGEOMETRY_H

#include <cstdlib>
#include <cmath>
#include <climits>
#include <cassert>
#include <utility>

template<class T>
class Vec3 {
    T point[3];
public:
    Vec3(T x = T(), T y = T(), T z = T()) {
        point[0] = x;
        point[1] = y;
        point[2] = z;
    }

    T &operator[](size_t i) {
        assert(i < 3);
        return point[(i < 0) ? 0 : i];
    }

    const T &operator[](size_t i) const {
        assert(i < 3);
        return point[(i < 0) ? 0 : i];
    }

    double length() {
        return sqrt(point[0] * point[0] + point[1] * point[1] + point[2] * point[2]);
    }

    Vec3<T> &normalize(T l = 1) {
        *this = (*this) * (l / length());
        return *this;
    }
    Vec3<T> reflect(const Vec3<T> &N) const {
        return *this - N * 2.0 * (*this * N);
    }

    T operator*(const Vec3<T> &right) const {
        T result = T();
        for (size_t i = 0; i < 3; ++i) {
            result += point[i] * right[i];
        };
        return result;
    }

    Vec3<T> operator+(const Vec3<T> &right) const {
        Vec3<T> result;
        for (size_t i = 0; i < 3; ++i) {
            result[i] = point[i] + right[i];
        }
        return result;
    }

    Vec3<T> operator-(const Vec3<T> &right) const {
        Vec3<T> result;
        for (size_t i = 0; i < 3; ++i) {
            result[i] = point[i] - right[i];
        }
        return result;
    }

    template<typename C>
    Vec3<T> operator*(const C &constant) const {
        Vec3<T> result;
        for (size_t i = 0; i < 3; ++i) {
            result[i] = point[i] * constant;
        }
        return result;
    }

    Vec3<T> operator-() const {
        return *this * T(-1);
    }
};

using Vec3d = Vec3<double>;
using Colour = Vec3<double>;
using Pixel = Vec3<double>;

class Light {
    Vec3d p;
    double intensity;

public:
    Light(const Vec3d &position, double intensity) : p(position), intensity(intensity) {
    }

    Vec3d getPosition() const {
        return p;
    }

    double getIntensity() const {
        return intensity;
    }
};

struct Material {
    std::pair<double, double> ambient_params;
    Colour diffuse_colour;
    double specular_param;

    Material(std::pair<double, double> ambient = {1, 0}, const Colour &diffuse = {}, double specular = {}) :
            ambient_params(std::move(ambient)),
            diffuse_colour(diffuse),
            specular_param(specular) {
    }
};

class Sphere {
    Vec3d center;
    double radius;
    Material material;
public:
    Sphere(const Vec3d &c, double r, const Material &mat) : center(c), radius(r), material(mat) {}

    bool areIntersected(const Vec3d &beamPoint, const Vec3d &direction, double &t0) const {
        Vec3d vB2C = center - beamPoint;
        double posB2C = vB2C * direction;
        double d2 = vB2C * vB2C - posB2C * posB2C;
        if (d2 > radius * radius) {
            return false;
        }
        double dist = sqrt(radius * radius - d2);
        t0 = posB2C - dist;
        double t1 = posB2C + dist;
        if (t0 < 0) {
            t0 = t1;
        }
        return t0 >= 0;
    }

    Vec3d getCenter() const {
        return center;
    }

    double getR() const {
        return radius;
    }

    Colour getColour() const {
        return material.diffuse_colour;
    }
};

#endif //RT_MYGEOMETRY_H
