//
// Created by jaden on 11/10/2022.
//

#ifndef RAY_TRACING_SHAPE_H
#define RAY_TRACING_SHAPE_H

#include "Ray.h"

class Shape {
    public:
        virtual bool hit(const Ray& ray) = 0;
        virtual Point3d& getCenter() = 0;
};

#endif //RAY_TRACING_SHAPE_H
