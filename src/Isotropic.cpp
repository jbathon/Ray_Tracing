//
// Created by jaden on 12/20/2022.
//

#include "Isotropic.h"


bool Isotropic::scatter(const Ray &rayIn, const HitRecord &rec, Color3d &attenuation, Ray &scattered) const {
    scattered = Ray(rec.p_, randomInUnitSphere(), rayIn.time());
    attenuation = albedo->value(rec.u_, rec.v_, rec.p_);
    return true;
}