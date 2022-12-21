//
// Created by jaden on 12/20/2022.
//

#include "Box.h"

Box::Box(const Point3d& p0, const Point3d& p1, shared_ptr<Material> ptr) {
    boxMin_ = p0;
    boxMax_ = p1;

    sides_.add(make_shared<XYRect>(p0.x(), p1.x(), p0.y(), p1.y(), p1.z(), ptr));
    sides_.add(make_shared<XYRect>(p0.x(), p1.x(), p0.y(), p1.y(), p0.z(), ptr));

    sides_.add(make_shared<XZRect>(p0.x(), p1.x(), p0.z(), p1.z(), p1.y(), ptr));
    sides_.add(make_shared<XZRect>(p0.x(), p1.x(), p0.z(), p1.z(), p0.y(), ptr));

    sides_.add(make_shared<YZRect>(p0.y(), p1.y(), p0.z(), p1.z(), p1.x(), ptr));
    sides_.add(make_shared<YZRect>(p0.y(), p1.y(), p0.z(), p1.z(), p0.x(), ptr));
}

bool Box::hit(const Ray& ray, double minT, double maxT, HitRecord& rec) const {
    return sides_.hit(ray, minT, maxT, rec);
}

bool Box::boundingBox(double time0, double time1, AABB &outputBox) const {
    outputBox = AABB(boxMin_, boxMax_);
    return true;
}