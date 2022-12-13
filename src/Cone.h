//
// Created by jaden on 11/10/2022.
//

#ifndef RAY_TRACING_CONE_H
#define RAY_TRACING_CONE_H

#include "HittableInterface.h"

class Cone : public HittableInterface {
    private:
        Point3d apex_;
        double radius_;
        double height_;
        double alpha_;
    public:
        Cone(const Point3d& center, double radius, double height);
        ~Cone();
        double hit(const Ray& ray);
//        Point3d& getCenter();
//        double getRadius();
//        double getHeight();
};


#endif //RAY_TRACING_CONE_H
