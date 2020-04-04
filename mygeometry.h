#ifndef RT_MYGEOMETRY_H
#define RT_MYGEOMETRY_H

#include <cstdlib>
#include <cmath>
#include <climits>
#include <cassert>
#include <utility>

constexpr double EPS = 0.0001;
constexpr int refComplexity = 4;
constexpr int MAX_DIST = 1000;

template<class T>
class Triple {
    T point[3];
public:
    Triple(T x = T(), T y = T(), T z = T()) {
        point[0] = x;
        point[1] = y;
        point[2] = z;
    }

    T &operator[](size_t i) {
        return point[(i < 0) ? 0 : i];
    }

    const T &operator[](size_t i) const {
        return point[(i < 0) ? 0 : i];
    }

    double length() const {
        return sqrt(point[0] * point[0] + point[1] * point[1] + point[2] * point[2]);
    }

    Triple<T> &normalize(T l = 1) {
        *this = (*this) * (l / length());
        return *this;
    }

    Triple<T> normalized(T l = 1) const {
        return (*this) * (l / length());
    }

    Triple<T> reflect(const Triple<T> &N) const {
        return *this - N * 2.0 * (*this * N);
    }

    T operator*(const Triple<T> &right) const {
        T result = T();
        for (size_t i = 0; i < 3; ++i) {
            result += point[i] * right[i];
        };
        return result;
    }

    Triple<T> operator+(const Triple<T> &right) const {
        Triple<T> result;
        for (size_t i = 0; i < 3; ++i) {
            result[i] = point[i] + right[i];
        }
        return result;
    }

    Triple<T> operator-(const Triple<T> &right) const {
        Triple<T> result;
        for (size_t i = 0; i < 3; ++i) {
            result[i] = point[i] - right[i];
        }
        return result;
    }

    template<typename C>
    Triple<T> operator*(const C &constant) const {
        Triple<T> result;
        for (size_t i = 0; i < 3; ++i) {
            result[i] = point[i] * constant;
        }
        return result;
    }

    Triple<T> operator-() const {
        return *this * T(-1);
    }
};

using Point = Triple<double>;
using Colour = Triple<double>;
using ReflectionParams = Triple<double>;
using RefractionParams = Triple<double>;
using DiffusiveParams = Triple<double>;
using Pixel = Triple<double>;

class Light {
    Point p;
    double intensity;

public:
    Light(const Point &position, double intensity) : p(position), intensity(intensity) {
    }

    Point getPosition() const {
        return p;
    }

    double getIntensity() const {
        return intensity;
    }
};

struct Material {
    ReflectionParams reflectionParams;
    DiffusiveParams diffusiveParams;
    double specularParam;
    double refractiveParam;
    double refractiveIndex;

    Material(const ReflectionParams &reflect = {1, 0, 0}, const DiffusiveParams &diffuse = {}, double specular = {},
             double refraction = {}, double refIdx = {}) :
            reflectionParams(reflect),
            diffusiveParams(diffuse),
            specularParam(specular),
            refractiveParam(refraction),
            refractiveIndex(refIdx) {
    }
};

class Sphere {
    Point center;
    double radius;
    Material material;
public:
    Sphere(const Point &c, double r, const Material &mat) : center(c), radius(r), material(mat) {}

    bool areIntersected(const Point &beamPoint, const Point &direction, double &t0) const {
        Point vB2C = center - beamPoint;
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
        return !(t0 < 0);
    }

    Point getCenter() const {
        return center;
    }

    double getR() const {
        return radius;
    }

    Material getMaterial() const {
        return material;
    }

    DiffusiveParams getDiffusiveParams() const {
        return material.diffusiveParams;
    }

    ReflectionParams getReflectionParams() const {
        return material.reflectionParams;
    }
};

class Plane {
    Point normal;
    Point point;
    Material material1;
    Material material2;
public:
    Plane(const Point &point, const Point &normal, const Material &mat1, const Material &mat2) :
            normal(normal.normalized()), point(point), material1(mat1), material2(mat2) {
    }

    Material getMaterial(Point &p) const {
        return (((int) (0.4 * p[0] + 100) + (int) (0.4 * p[2])) % 2) ? material1 : material2;
    }

    Point getNormal() const {
        return normal;
    }

    Point getPoint() const {
        return point;
    }

    bool areIntersected(const Point &beamPoint, const Point &direction, double &t0) const {
        if (std::abs(direction * normal) > EPS) {
            double plane_dist = -1.0 * ((beamPoint - point) * normal) / (direction * normal);
            if (plane_dist > 0)
                t0 = plane_dist;
            return true;
        }
        return false;
    }
};


#endif //RT_MYGEOMETRY_H
