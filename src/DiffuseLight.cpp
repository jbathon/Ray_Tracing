//
// Created by jaden on 12/20/2022.
//

#include "DiffuseLight.h"

bool DiffuseLight::scatter(const Ray& rayIn, const HitRecord& rec, Color3d& attenuation, Ray& scattered) const {
    return false;
}

Color3d DiffuseLight::emitted(double u, double v, const Point3d &p) const {
    return emit_->value(u, v, p);
}