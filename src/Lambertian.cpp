//
// Created by jaden on 12/20/2022.
//

#include "Lambertian.h"

bool Lambertian::scatter(const Ray &rayIn, const HitRecord &rec, Color3d &attenuation, Ray &scattered) const {
    auto scatter_direction = rec.normal_ + randomUnitVector();

    // Catch degenerate scatter direction
    if (scatter_direction.near_zero())
        scatter_direction = rec.normal_;

    scattered = Ray(rec.p_, scatter_direction, rayIn.time());
    attenuation = albedo->value(rec.u_, rec.v_, rec.p_);
    return true;
}