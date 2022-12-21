//
// Created by jaden on 11/10/2022.
//

#include "Sphere.h"

Sphere::Sphere(const Point3d& center, double radius, shared_ptr<Material> m) {
    center_ = center;
    radius_ = radius;
    matPtr_ = m;
}

Sphere::~Sphere() {

}

Point3d &Sphere::center() {
    return center_;
}

bool Sphere::hit(const Ray& ray, double minT, double maxT, HitRecord& rec) const {
    Vector3d oc = ray.origin() - center_;
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
    Vector3d outward_normal = (rec.p_ - center_) / radius_;
    rec.setFaceNormal(ray, outward_normal);
    getSphereUV(outward_normal, rec.u_, rec.v_);
    rec.matPtr_ = matPtr_;

    return true;
}

bool Sphere::boundingBox(double time0, double time1, AABB &outputBox) const {
    outputBox = AABB(
            center_ - Vector3d(radius_,radius_,radius_),
            center_ + Vector3d(radius_,radius_,radius_));
    return true;
}

void Sphere::getSphereUV(const Point3d &p, double &u, double &v) {
    auto theta = acos(-p.y());
    auto phi = atan2(-p.z(), p.x()) + pi;

    u = phi / (2*pi);
    v = theta / pi;
}