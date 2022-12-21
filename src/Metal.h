//
// Created by jaden on 12/20/2022.
//

#ifndef RAY_TRACING_METAL_H
#define RAY_TRACING_METAL_H

#endif //RAY_TRACING_METAL_H

#include "Material.h"

class Metal : public Material {

    private:
        Color3d albedo;
        double fuzz;
    public:
        Metal(const Color3d& a, double f) : albedo(a), fuzz(f < 1 ? f : 1) {}

        virtual bool scatter(
                const Ray& rIn, const HitRecord& rec, Color3d& attenuation, Ray& scattered
        ) const override;

};