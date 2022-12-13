//
// Created by jaden on 11/10/2022.
//

#ifndef RAY_TRACING_SPHERE_H
#define RAY_TRACING_SPHERE_H

#include "HittableInterface.h"

class Sphere : public HittableInterface {
    private:
        Point3d center_;
        double radius_;
    public:
        Sphere() {};
        Sphere(const Point3d& center, double radius);
        ~Sphere();
        virtual bool hit(const Ray& ray, double minT, double maxT, HitRecord& rec) const override;
        Point3d& center();
        double radius();

};


#endif //RAY_TRACING_SPHERE_H
