//
// Created by jaden on 12/20/2022.
//

#include "BVH.h"
#include <algorithm>

BVHNode::BVHNode(const HittableList &list, double time0, double time1) {
    BVHNode(list.objects_,0,list.objects_.size(),time0,time1);
}

BVHNode::BVHNode(const std::vector<shared_ptr<HittableInterface>> &src_objects, size_t start, size_t end, double time0,
                 double time1) {
    auto objects = src_objects; // Create a modifiable array of the source scene objects

    int axis = randomInt(0,2);
    auto comparator = (axis == 0) ? boxXCompare
                                  : (axis == 1) ? boxYCompare
                                                : boxZCompare;

    size_t object_span = end - start;

    if (object_span == 1) {
        left = right = objects[start];
    } else if (object_span == 2) {
        if (comparator(objects[start], objects[start+1])) {
            left = objects[start];
            right = objects[start+1];
        } else {
            left = objects[start+1];
            right = objects[start];
        }
    } else {
        std::sort(objects.begin() + start, objects.begin() + end, comparator);

        auto mid = start + object_span/2;
        left = make_shared<BVHNode>(objects, start, mid, time0, time1);
        right = make_shared<BVHNode>(objects, mid, end, time0, time1);
    }

    AABB box_left, box_right;

    if (  !left->boundingBox (time0, time1, box_left)
          || !right->boundingBox(time0, time1, box_right)
            )
        std::cerr << "No bounding box in bvh_node constructor.\n";

    box = surroundingBox(box_left, box_right);
}

bool BVHNode::hit(const Ray &ray, double minT, double maxT, HitRecord &rec) const {
    if (!box.hit(ray, minT, maxT))
        return false;

    bool hit_left = left->hit(ray, minT, maxT, rec);
    bool hit_right = right->hit(ray, minT, hit_left ? rec.t_ : maxT, rec);

    return hit_left || hit_right;
}

bool BVHNode::boundingBox(double time0, double time1, AABB &outputBox) const {
    outputBox = box;
    return true;
}