//
// Created by jaden on 12/20/2022.
//

#ifndef RAY_TRACING_CONSTANTMEDIUN_H
#define RAY_TRACING_CONSTANTMEDIUN_H

#include "Utilities.h"
#include "HittableInterface.h"
#include "Material.h"
#include "Isotropic.h"

class ConstantMedium : HittableInterface {
    private:
        shared_ptr<HittableInterface> boundary_;
        shared_ptr<Material> phaseFunction_;
        double negInvDensity_;
    public:
        ConstantMedium(shared_ptr<HittableInterface> b, double d, shared_ptr<Texture> a)
        : boundary_(b), negInvDensity_(-1/d), phaseFunction_(make_shared<Isotropic>(a))
        {}

        ConstantMedium(shared_ptr<HittableInterface> b, double d, Color3d c)
        : boundary_(b), negInvDensity_(-1/d), phaseFunction_(make_shared<Isotropic>(c)){}

        virtual bool hit(const Ray& ray, double minT, double maxT, HitRecord& rec) const override;
        virtual bool boundingBox(double time0, double time1, AABB& outputBox) const override;

};


#endif //RAY_TRACING_CONSTANTMEDIUN_H
