//
// Created by jaden on 11/10/2022.
//

#ifndef RAY_TRACING_SPHERE_H
#define RAY_TRACING_SPHERE_H

#include "HittableInterface.h"

class Sphere : public HittableInterface {
    private:
        Point3d center_;
        double radius_;
        shared_ptr<Material> matPtr_;
    public:
        Sphere() {};
        Sphere(const Point3d& center, double radius, shared_ptr<Material> m);
        ~Sphere();
        virtual bool hit(const Ray& ray, double minT, double maxT, HitRecord& rec) const override;
        virtual bool boundingBox(double time0, double time1, AABB& outputBox) const override;
        static void getSphereUV(const Point3d& p, double& u, double& v);
        Point3d& center();
        double radius();

};


#endif //RAY_TRACING_SPHERE_H
