//
// Created by jaden on 11/10/2022.
//

#ifndef RAY_TRACING_HITTABLEINTERFACE_H
#define RAY_TRACING_HITTABLEINTERFACE_H

#include "AABB.h"

class Material;

struct HitRecord {
    Point3d p_;
    Vector3d normal_;
    double t_;
    double u_;
    double v_;
    shared_ptr<Material> matPtr_;
    bool frontFace_;

    inline void setFaceNormal(const Ray& ray, const Vector3d& outwardNormal) {
        frontFace_ = dot(ray.direction(), outwardNormal) < 0;
        normal_ = frontFace_ ? outwardNormal : -outwardNormal;
    }
};
class HittableInterface {
    public:
        virtual bool hit(const Ray& ray, double minT, double maxT, HitRecord& rec) const = 0;
        virtual bool boundingBox(double time0, double time1, AABB& outputBox) const = 0;
};

#endif //RAY_TRACING_HITTABLEINTERFACE_H
