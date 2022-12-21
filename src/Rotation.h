//
// Created by jaden on 12/20/2022.
//

#ifndef RAY_TRACING_ROTATION_H
#define RAY_TRACING_ROTATION_H

#include "HittableInterface.h"

class RotateY : public HittableInterface {
public:
    RotateY(shared_ptr<HittableInterface> p, double angle);

    virtual bool hit(const Ray& ray, double minT, double maxT, HitRecord& rec) const override;
    virtual bool boundingBox(double time0, double time1, AABB& outputBox) const override;

public:
    shared_ptr<HittableInterface> ptr_;
    double sinTheta_;
    double cosTheta_;
    bool hasBox_;
    AABB bbox_;
};


#endif //RAY_TRACING_ROTATION_H
