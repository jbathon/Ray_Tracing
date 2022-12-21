//
// Created by jaden on 12/20/2022.
//

#ifndef RAY_TRACING_BVH_H
#define RAY_TRACING_BVH_H

#endif //RAY_TRACING_BVH_H

#include "Utilities.h"
#include "HittableInterface.h"
#include "HittableList.h"

class BVHNode : public HittableInterface {
public:
    BVHNode();

    BVHNode(const HittableList& list, double time0, double time1);

    BVHNode(
            const std::vector<shared_ptr<HittableInterface>>& src_objects,
            size_t start, size_t end, double time0, double time1);

    virtual bool hit(const Ray& ray, double minT, double maxT, HitRecord& rec) const override;
    virtual bool boundingBox(double time0, double time1, AABB& outputBox) const override;

private:
    shared_ptr<HittableInterface> left;
    shared_ptr<HittableInterface> right;
    AABB box;
};

inline bool boxCompare(const shared_ptr<HittableInterface> a, const shared_ptr<HittableInterface> b, int axis) {
    AABB box_a;
    AABB box_b;

    if (!a->boundingBox(0,0, box_a) || !b->boundingBox(0,0, box_b))
        std::cerr << "No bounding box in bvh_node constructor.\n";

    return box_a.min().coords[axis] < box_b.min().coords[axis];
}


bool boxXCompare (const shared_ptr<HittableInterface> a, const shared_ptr<HittableInterface> b) {
    return boxCompare(a, b, 0);
}

bool boxYCompare (const shared_ptr<HittableInterface> a, const shared_ptr<HittableInterface> b) {
    return boxCompare(a, b, 1);
}

bool boxZCompare (const shared_ptr<HittableInterface> a, const shared_ptr<HittableInterface> b) {
    return boxCompare(a, b, 2);
}