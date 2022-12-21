//
// Created by jaden on 12/20/2022.
//

#include "ConstantMedium.h"

bool ConstantMedium::hit(const Ray &ray, double minT, double maxT, HitRecord &rec) const {
    const bool enableDebug = false;
    const bool debugging = enableDebug && randomDouble() < 0.00001;

    HitRecord rec1, rec2;

    if (!boundary_->hit(ray, -infinity, infinity, rec1))
        return false;

    if (!boundary_->hit(ray, rec1.t_+0.0001, infinity, rec2))
        return false;

    if (debugging) std::cerr << "\nt_min=" << rec1.t_ << ", t_max=" << rec2.t_ << '\n';

    if (rec1.t_ < minT) rec1.t_ = minT;
    if (rec2.t_ > maxT) rec2.t_ = maxT;

    if (rec1.t_ >= rec2.t_)
        return false;

    if (rec1.t_ < 0)
        rec1.t_ = 0;

    const auto ray_length = ray.direction().length();
    const auto distance_inside_boundary = (rec2.t_ - rec1.t_) * ray_length;
    const auto hit_distance = negInvDensity_ * log(randomDouble());

    if (hit_distance > distance_inside_boundary)
        return false;

    rec.t_ = rec1.t_ + hit_distance / ray_length;
    rec.p_ = ray.at(rec.t_);

    if (debugging) {
        std::cerr << "hit_distance = " <<  hit_distance << '\n'
                  << "rec.t = " <<  rec.t_ << '\n'
                  << "rec.p = " <<  rec.p_ << '\n';
    }

    rec.normal_ = Vector3d(1,0,0);  // arbitrary
    rec.frontFace_ = true;     // also arbitrary
    rec.matPtr_ = phaseFunction_;

    return true;
}

bool ConstantMedium::boundingBox(double time0, double time1, AABB &outputBox) const {
    return boundary_->boundingBox(time0, time1, outputBox);
}