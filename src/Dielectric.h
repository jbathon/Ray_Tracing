//
// Created by jaden on 12/20/2022.
//

#ifndef RAY_TRACING_DIELECTRIC_H
#define RAY_TRACING_DIELECTRIC_H

#endif //RAY_TRACING_DIELECTRIC_H
#include "Material.h"

class Dielectric : public Material {
public:
    Dielectric(double index_of_refraction) : ir(index_of_refraction) {}

    virtual bool scatter(
            const Ray& rayIn, const HitRecord& rec, Color3d& attenuation, Ray& scattered
    ) const override;

private:
    double ir; // Index of Refraction
    static double reflectance(double cosine, double ref_idx);
};