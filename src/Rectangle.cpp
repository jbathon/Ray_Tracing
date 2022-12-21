//
// Created by jaden on 12/20/2022.
//

#include "Rectangle.h"



// XY
bool XYRect::hit(const Ray &ray, double minT, double maxT, HitRecord &rec) const {
    auto t = (k-ray.origin().z()) / ray.direction().z();
    if (t < minT || t > maxT)
        return false;
    auto x = ray.origin().x() + t*ray.direction().x();
    auto y = ray.origin().y() + t*ray.direction().y();
    if (x < x0 || x > x1 || y < y0 || y > y1)
        return false;
    rec.u_ = (x-x0)/(x1-x0);
    rec.v_ = (y-y0)/(y1-y0);
    rec.t_ = t;
    auto outward_normal = Vector3d(0, 0, 1);
    rec.setFaceNormal(ray, outward_normal);
    rec.matPtr_ = mp_;
    rec.p_ = ray.at(t);
    return true;
}

bool XYRect::boundingBox(double time0, double time1, AABB &outputBox) const {
    outputBox = AABB(Point3d(x0,y0, k-0.0001), Point3d(x1, y1, k+0.0001));
    return true;
}

// YZ

bool YZRect::hit(const Ray &ray, double minT, double maxT, HitRecord &rec) const {
    auto t = (k-ray.origin().x()) / ray.direction().x();
    if (t < minT || t > maxT)
        return false;
    auto y = ray.origin().y() + t*ray.direction().y();
    auto z = ray.origin().z() + t*ray.direction().z();
    if (y < y0 || y > y1 || z < z0 || z > z1)
        return false;
    rec.u_ = (y-y0)/(y1-y0);
    rec.v_ = (z-z0)/(z1-z0);
    rec.t_ = t;
    auto outward_normal = Vector3d(1, 0, 0);
    rec.setFaceNormal(ray, outward_normal);
    rec.matPtr_ = mp_;
    rec.p_ = ray.at(t);
    return true;
}

bool YZRect::boundingBox(double time0, double time1, AABB &outputBox) const {
    outputBox = AABB(Point3d(k-0.0001, y0, z0), Point3d(k+0.0001, y1, z1));
    return true;
}


// XZ
bool XZRect::hit(const Ray &ray, double minT, double maxT, HitRecord &rec) const {
    auto t = (k-ray.origin().y()) / ray.direction().y();
    if (t < minT|| t > maxT)
        return false;
    auto x = ray.origin().x() + t*ray.direction().x();
    auto z = ray.origin().z() + t*ray.direction().z();
    if (x < x0 || x > x1 || z < z0 || z > z1)
        return false;
    rec.u_ = (x-x0)/(x1-x0);
    rec.v_ = (z-z0)/(z1-z0);
    rec.t_ = t;
    auto outward_normal = Vector3d(0, 1, 0);
    rec.setFaceNormal(ray, outward_normal);
    rec.matPtr_ = mp_;
    rec.p_ = ray.at(t);
    return true;
}

bool XZRect::boundingBox(double time0, double time1, AABB &outputBox) const {
    outputBox = AABB(Point3d(x0,k-0.0001,z0), Point3d(x1, k+0.0001, z1));
    return true;
}