//
// Created by jaden on 12/12/2022.
//

#include "HittableList.h"

void HittableList::clear() {
    objects_.clear();
}

HittableList::HittableList(){}
void HittableList::add(shared_ptr<HittableInterface> object) {
    objects_.push_back(object);
}

bool HittableList::hit(const Ray& ray, double minT, double maxT, HitRecord& rec) const {
    HitRecord temp_rec;
    bool hit_anything = false;
    auto closest_so_far = maxT;

    for (const auto& object : objects_) {
        if (object->hit(ray, minT, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t_;
            rec = temp_rec;
        }
    }

    return hit_anything;
}
