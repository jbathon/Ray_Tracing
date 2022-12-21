//
// Created by jaden on 12/20/2022.
//

#include "Rotation.h"

RotateY::RotateY(shared_ptr<HittableInterface> p, double angle) {
    ptr_ = p;
    auto radians = degreesToRadians(angle);
    sinTheta_ = sin(radians);
    cosTheta_ = cos(radians);
    hasBox_ = ptr_->boundingBox(0, 1, bbox_);

    Point3d min( infinity,  infinity,  infinity);
    Point3d max(-infinity, -infinity, -infinity);

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                auto x = i*bbox_.max().x() + (1-i)*bbox_.min().x();
                auto y = j*bbox_.max().y() + (1-j)*bbox_.min().y();
                auto z = k*bbox_.max().z() + (1-k)*bbox_.min().z();

                auto newx =  cosTheta_*x + sinTheta_*z;
                auto newz = -sinTheta_*x + cosTheta_*z;

                Vector3d tester(newx, y, newz);

                for (int c = 0; c < 3; c++) {
                    min[c] = fmin(min[c], tester[c]);
                    max[c] = fmax(max[c], tester[c]);
                }
            }
        }
    }

    bbox_ = AABB(min, max);
}

bool RotateY::hit(const Ray &ray, double minT, double maxT, HitRecord &rec) const {
    auto origin = ray.origin();
    auto direction = ray.direction();

    origin[0] = cosTheta_*ray.origin()[0] - sinTheta_*ray.origin()[2];
    origin[2] = sinTheta_*ray.origin()[0] + cosTheta_*ray.origin()[2];

    direction[0] = cosTheta_*ray.direction()[0] - sinTheta_*ray.direction()[2];
    direction[2] = sinTheta_*ray.direction()[0] + cosTheta_*ray.direction()[2];

    Ray rotatedRay(origin, direction, ray.time());

    if (!ptr_->hit(rotatedRay, minT, maxT, rec))
        return false;

    auto p = rec.p_;
    auto normal = rec.normal_;

    p[0] =  cosTheta_*rec.p_[0] + sinTheta_*rec.p_[2];
    p[2] = -sinTheta_*rec.p_[0] + cosTheta_*rec.p_[2];

    normal[0] =  cosTheta_*rec.normal_[0] + sinTheta_*rec.normal_[2];
    normal[2] = -sinTheta_*rec.normal_[0] + cosTheta_*rec.normal_[2];

    rec.p_ = p;
    rec.setFaceNormal(rotatedRay, normal);

    return true;
}

bool RotateY::boundingBox(double time0, double time1, AABB &outputBox) const {
    outputBox = bbox_;
    return hasBox_;
}