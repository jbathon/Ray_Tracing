//
// Created by jaden on 11/6/2022.
//

#include "Ray.h"

Ray::Ray(const Point3d &origin, const Vector3d &direction, double time) {
    orig_ = origin;
    dir_ = direction;
    time_ = time;
}

Point3d Ray::origin() const {
    return orig_;
}

Vector3d Ray::direction() const {
    return dir_;
}

double Ray::time() const {
    return time_;
}

Point3d Ray::at(double t) const {
    return orig_ + t * dir_;
}