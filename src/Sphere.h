//
// Created by jaden on 11/10/2022.
//

#ifndef RAY_TRACING_SPHERE_H
#define RAY_TRACING_SPHERE_H

#include "Shape.h"

class Sphere : public Shape {
    private:
        Point3d center;
        double radius;
    public:
        Sphere(const Point3d& center, double radius);
        ~Sphere();
        bool hit(const Ray& ray);
        Point3d& getCenter();
        double getRadius();
};


#endif //RAY_TRACING_SPHERE_H
