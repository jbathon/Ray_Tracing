//
// Created by jaden on 11/6/2022.
//

#ifndef OPENGL_RAY_TRACING_RAY_H
#define OPENGL_RAY_TRACING_RAY_H

#include "Vector3d.h"


class Ray {
    private:
        Point3d orig;
        Vector3d dir;
    public:
        Ray(const Point3d& origin, const Vector3d& direction);

        Point3d origin() const;
        Vector3d direction() const;

        Point3d at(GLdouble t) const;
};


#endif //OPENGL_RAY_TRACING_RAY_H
