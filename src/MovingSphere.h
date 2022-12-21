//
// Created by jaden on 12/20/2022.
//

#ifndef RAY_TRACING_MOVINGSPHERE_H
#define RAY_TRACING_MOVINGSPHERE_H

#include "Utilities.h"
#include "HittableInterface.h"

class MovingSphere : public HittableInterface {
    private:
        Point3d center0_, center1_;
        double time0_, time1_;
        double radius_;
        shared_ptr<Material> matPtr_;

    public:
        MovingSphere() {}
        MovingSphere(
                Point3d cen0, Point3d cen1, double time0, double time1, double r, shared_ptr<Material> m);

        virtual bool hit(const Ray& ray, double minT, double maxT, HitRecord& rec) const override;
        virtual bool boundingBox(double time0, double time1, AABB& outputBox) const override;

        Point3d center(double time) const;
};



#endif //RAY_TRACING_MOVINGSPHERE_H
