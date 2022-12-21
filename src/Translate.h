//
// Created by jaden on 12/20/2022.
//

#ifndef RAY_TRACING_TRANSLATE_H
#define RAY_TRACING_TRANSLATE_H

#include "HittableInterface.h"

class Translate : public HittableInterface {
public:
    Translate(shared_ptr<HittableInterface> p, const Vector3d& displacement)
            : ptr_(p), offset_(displacement) {}

    virtual bool hit(const Ray& ray, double minT, double maxT, HitRecord& rec) const override;
    virtual bool boundingBox(double time0, double time1, AABB& outputBox) const override;

private:
    shared_ptr<HittableInterface> ptr_;
    Vector3d offset_;
};


#endif //RAY_TRACING_TRANSLATE_H
