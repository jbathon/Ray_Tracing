//
// Created by jaden on 12/20/2022.
//

#include "MovingSphere.h"

MovingSphere::MovingSphere(Point3d cen0, Point3d cen1, double time0, double time1, double r, shared_ptr<Material> m) {
    center0_ = cen0;
    center1_ = cen1;
    time0_ = time0;
    time1_ = time1;
    radius_ = r;
    matPtr_ = m;
}

Point3d MovingSphere::center(double time) const {
    return center0_ + ((time - time0_) / (time1_ - time0_)) * (center1_ - center0_);
}

bool MovingSphere::hit(const Ray& ray, double minT, double maxT, HitRecord& rec) const {
    Vector3d oc = ray.origin() - center(ray.time());
    auto a = ray.direction().length_squared();
    auto half_b = dot(oc, ray.direction());
    auto c = oc.length_squared() - radius_ * radius_;

    auto discriminant = half_b*half_b - a*c;
    if (discriminant < 0) return false;
    auto sqrtd = sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    auto root = (-half_b - sqrtd) / a;
    if (root < minT || maxT < root) {
        root = (-half_b + sqrtd) / a;
        if (root < minT || maxT < root)
            return false;
    }

    rec.t_ = root;
    rec.p_ = ray.at(rec.t_);
    Vector3d outward_normal = (rec.p_ - center(ray.time())) / radius_;
    rec.setFaceNormal(ray, outward_normal);
    rec.matPtr_ = matPtr_;
}

bool MovingSphere::boundingBox(double time0, double time1, AABB &outputBox) const {
    AABB box0(
            center(time0) - Vector3d(radius_, radius_, radius_),
            center(time0) + Vector3d(radius_, radius_, radius_));
    AABB box1(
            center(time1) - Vector3d(radius_, radius_, radius_),
            center(time1) + Vector3d(radius_, radius_, radius_));
    outputBox = surroundingBox(box0, box1);
    return true;
}

