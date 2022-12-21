//
// Created by jaden on 12/20/2022.
//

#ifndef RAY_TRACING_BOX_H
#define RAY_TRACING_BOX_H

#include "Rectangle.h"
#include "HittableList.h"

class Box : public HittableInterface{
    public:
        Box() {}
        Box(const Point3d& p0, const Point3d& p1, shared_ptr<Material> ptr);


    virtual bool hit(const Ray& ray, double minT, double maxT, HitRecord& rec) const override;
    virtual bool boundingBox(double time0, double time1, AABB& outputBox) const override;

    public:
        Point3d boxMin_;
        Point3d boxMax_;
        HittableList sides_;

};


#endif //RAY_TRACING_BOX_H
