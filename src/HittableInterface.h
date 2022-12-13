//
// Created by jaden on 11/10/2022.
//

#ifndef RAY_TRACING_HITTABLEINTERFACE_H
#define RAY_TRACING_HITTABLEINTERFACE_H

#include "Ray.h"

struct HitRecord {
    Point3d p_;
    Vector3d normal_;
    double t_;
    bool frontFace_;

    inline void setFaceNormal(const Ray& ray, const Vector3d& outwardNormal) {
        frontFace_ = dot(ray.direction(), outwardNormal) < 0;
        normal_ = frontFace_ ? outwardNormal : -outwardNormal;
    }
};
class HittableInterface {
    public:
        virtual bool hit(const Ray& ray, double minT, double maxT, HitRecord& rec) const = 0;
};

#endif //RAY_TRACING_HITTABLEINTERFACE_H
