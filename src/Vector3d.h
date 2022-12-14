//
// Created by jaden on 11/6/2022.
//

#ifndef OPENGL_RAY_TRACING_VECTOR3D_H
#define OPENGL_RAY_TRACING_VECTOR3D_H

#include <GL/freeglut.h>
#include <cmath>
#include <iostream>


class Vector3d {
    public:
        double coords[3];
    public:
        Vector3d();
        Vector3d(double c1, double c2, double c3);
        ~Vector3d();

        double x() const;
        double y() const;
        double z() const;

        Vector3d operator-() const;
        double operator[](int i) const;
        double& operator[](int i);
        Vector3d& operator+=(const Vector3d &v);
        Vector3d& operator*=(const double t);
        Vector3d& operator/=(const double t);

        double length() const;
        double length_squared() const;

        Vector3d limitToRange(double minVal, double maxVal);
        static Vector3d random();
        static Vector3d random(double min,double max);

    bool near_zero() const {
        // Return true if the vector is close to zero in all dimensions.
        const auto s = 1e-8;
        return (fabs(coords[0]) < s) && (fabs(coords[1]) < s) && (fabs(coords[2]) < s);
    }
};

using Point3d = Vector3d;
using Color3d = Vector3d;


inline std::ostream& operator<<(std::ostream &out, const Vector3d &v) {
    return out << v[0] << ' ' << v[1] << ' ' << v[2];
}

inline Vector3d operator+(const Vector3d &u, const Vector3d &v) {
    return Vector3d(u[0] + v[0], u[1] + v[1], u[2] + v[2]);
}

inline Vector3d operator-(const Vector3d &u, const Vector3d &v) {
    return Vector3d(u[0] - v[0], u[1] - v[1], u[2] - v[2]);
}

inline Vector3d operator*(const Vector3d &u, const Vector3d &v) {
    return Vector3d(u[0] * v[0], u[1] * v[1], u[2] * v[2]);
}

inline Vector3d operator*(double t, const Vector3d &v) {
    return Vector3d(t * v[0], t * v[1], t * v[2]);
}

inline Vector3d operator*(const Vector3d &v, double t) {
    return t * v;
}

inline Vector3d operator/(Vector3d v, double t) {
    return (1/t) * v;
}

inline double dot(const Vector3d &u, const Vector3d&v) {
    return u[0] * v[0]
           + u[1] * v[1]
           + u[2] * v[2];
}

inline Vector3d cross(const Vector3d &u, const Vector3d &v) {
    return Vector3d(u[1] * v[2] - u[2] * v[1],
                    u[2] * v[0] - u[0] * v[2],
                    u[0] * v[1] - u[1] * v[0]);
}

inline Vector3d unitVector(Vector3d v) {
    return v / v.length();
}

inline Vector3d sqrt(Vector3d &v) {
    return Vector3d(sqrt(v[0]),sqrt(v[1]),sqrt(v[2]));
}

inline Vector3d randomInUnitSphere() {
    while (true) {
        auto p = Vector3d::random(-1,1);
        if (p.length_squared() >= 1) continue;
        return p;
    }
}




#endif //OPENGL_RAY_TRACING_VECTOR3D_H
