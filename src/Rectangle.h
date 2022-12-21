//
// Created by jaden on 12/20/2022.
//

#ifndef RAY_TRACING_XYRECT_H
#define RAY_TRACING_XYRECT_H

#include "HittableInterface.h"

class XYRect : public HittableInterface {
    public:
        XYRect() {}

        XYRect(double _x0, double _x1, double _y0, double _y1, double _k,
                shared_ptr<Material> mat)
                : x0(_x0), x1(_x1), y0(_y0), y1(_y1), k(_k), mp_(mat) {};

        virtual bool hit(const Ray& ray, double minT, double maxT, HitRecord& rec) const override;
        virtual bool boundingBox(double time0, double time1, AABB& outputBox) const override;

    public:
        shared_ptr<Material> mp_;
        double x0, x1, y0, y1, k;
};

class YZRect : public HittableInterface {
public:
    YZRect() {}

    YZRect(double _y0, double _y1, double _z0, double _z1, double _k,
           shared_ptr<Material> mat)
            : y0(_y0), y1(_y1), z0(_z0), z1(_z1), k(_k), mp_(mat) {};

    virtual bool hit(const Ray& ray, double minT, double maxT, HitRecord& rec) const override;
    virtual bool boundingBox(double time0, double time1, AABB& outputBox) const override;

public:
    shared_ptr<Material> mp_;
    double y0, y1, z0, z1, k;
};

class XZRect : public HittableInterface {
public:
    XZRect() {}

    XZRect(double _x0, double _x1, double _z0, double _z1, double _k,
            shared_ptr<Material> mat)
            : x0(_x0), x1(_x1), z0(_z0), z1(_z1), k(_k), mp_(mat) {};

    virtual bool hit(const Ray& ray, double minT, double maxT, HitRecord& rec) const override;
    virtual bool boundingBox(double time0, double time1, AABB& outputBox) const override;

public:
    shared_ptr<Material> mp_;
    double x0, x1, z0, z1, k;
};


#endif //RAY_TRACING_XYRECT_H
