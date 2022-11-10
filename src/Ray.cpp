//
// Created by jaden on 11/6/2022.
//

#include "Ray.h"

Ray::Ray(const Point3d &origin, const Vector3d &direction) {
    orig = origin;
    dir = direction;
}

Point3d Ray::origin() const {
    return orig;
}

Vector3d Ray::direction() const {
    return dir;
}

Point3d Ray::at(GLdouble t) const {
    return orig + t*dir;
}