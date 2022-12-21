//
// Created by jaden on 12/12/2022.
//

#ifndef RAY_TRACING_HITTABLELIST_H
#define RAY_TRACING_HITTABLELIST_H

#include "HittableInterface.h"

#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

class HittableList : public HittableInterface {
    public:
        std::vector<shared_ptr<HittableInterface>> objects_;
    public:
        HittableList();
        HittableList(shared_ptr<HittableInterface> object) { add(object); }

        void clear();
        void add(shared_ptr<HittableInterface> object);

        virtual bool hit(const Ray& ray, double minT, double maxT, HitRecord& rec) const override;
        virtual bool boundingBox(double time0, double time1, AABB& outputBox) const override;
};


#endif //RAY_TRACING_HITTABLELIST_H
