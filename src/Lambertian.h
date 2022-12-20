//
// Created by jaden on 12/20/2022.
//

#ifndef RAY_TRACING_LAMBERTIAN_H
#define RAY_TRACING_LAMBERTIAN_H

#include "Material.h"

class Lambertian : public Material {
    private:
        Color3d albedo;
    public:
        Lambertian(const Color3d& a) : albedo(a) {}

        virtual bool scatter(
                const Ray& rayIn, const HitRecord& rec, Color3d& attenuation, Ray& scattered
        )  const override {
            auto scatter_direction = rec.normal_ + randomUnitVector();

            // Catch degenerate scatter direction
            if (scatter_direction.near_zero())
                scatter_direction = rec.normal_;

            scattered = Ray(rec.p_, scatter_direction);
            attenuation = albedo;
            return true;
        }
};


#endif //RAY_TRACING_LAMBERTIAN_H
