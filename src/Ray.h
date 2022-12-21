//
// Created by jaden on 11/6/2022.
//

#ifndef OPENGL_RAY_TRACING_RAY_H
#define OPENGL_RAY_TRACING_RAY_H

#include "Vector3d.h"


class Ray {
    private:
        Point3d orig_;
        Vector3d dir_;
        double time_;
    public:
        Ray() {};
        Ray(const Point3d& origin, const Vector3d& direction, double time = 0.0);

        Point3d origin() const;
        Vector3d direction() const;
        double time() const;

        Point3d at(GLdouble t) const;
};


#endif //OPENGL_RAY_TRACING_RAY_H
