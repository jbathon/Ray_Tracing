//
// Created by jaden on 12/20/2022.
//

#include "Translate.h"

bool Translate::hit(const Ray& ray, double minT, double maxT, HitRecord& rec) const {
    Ray movedRay(ray.origin() - offset_, ray.direction(), ray.time());
    if (!ptr_->hit(movedRay, minT, maxT, rec))
        return false;

    rec.p_ += offset_;
    rec.setFaceNormal(movedRay, rec.normal_);

    return true;
}

bool Translate::boundingBox(double time0, double time1, AABB& outputBox) const {
    if (!ptr_->boundingBox(time0, time1, outputBox))
        return false;

    outputBox = AABB(
            outputBox.min() + offset_,
            outputBox.max() + offset_);

    return true;
}