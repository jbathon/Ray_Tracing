//
// Created by jaden on 11/10/2022.
//

#include "Sphere.h"

Sphere::Sphere(const Point3d& center, double radius) {
    center_ = center;
    radius_ = radius;
}

Sphere::~Sphere() {

}

Point3d &Sphere::center() {
    return center_;
}

bool Sphere::hit(const Ray& ray, double t_min, double t_max, HitRecord& rec) const {
    Vector3d oc = ray.origin() - center_;
    auto a = ray.direction().length_squared();
    auto half_b = dot(oc, ray.direction());
    auto c = oc.length_squared() - radius_ * radius_;

    auto discriminant = half_b*half_b - a*c;
    if (discriminant < 0) return false;
    auto sqrtd = sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    auto root = (-half_b - sqrtd) / a;
    if (root < t_min || t_max < root) {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || t_max < root)
            return false;
    }

    rec.t_ = root;
    rec.p_ = ray.at(rec.t_);
    Vector3d outward_normal = (rec.p_ - center_) / radius_;
    rec.setFaceNormal(ray, outward_normal);

    return true;
}