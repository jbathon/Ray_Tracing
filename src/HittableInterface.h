//
// Created by jaden on 11/10/2022.
//

#ifndef RAY_TRACING_SHAPEINTERFACE_H
#define RAY_TRACING_SHAPEINTERFACE_H

#include "Ray.h"

class ShapeInterface {
    public:
        virtual bool hit(const Ray& ray) = 0;
};

#endif //RAY_TRACING_SHAPEINTERFACE_H
