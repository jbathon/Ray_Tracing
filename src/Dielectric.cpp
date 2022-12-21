//
// Created by jaden on 12/20/2022.
//
#include "Dielectric.h"

bool Dielectric::scatter(const Ray &rayIn, const HitRecord &rec, Color3d &attenuation, Ray &scattered) const {
    attenuation = Color3d(1.0, 1.0, 1.0);
    double refraction_ratio = rec.frontFace_ ? (1.0/ir) : ir;

    Vector3d unit_direction = unitVector(rayIn.direction());
    double cos_theta = fmin(dot(-unit_direction, rec.normal_), 1.0);
    double sin_theta = sqrt(1.0 - cos_theta*cos_theta);

    bool cannot_refract = refraction_ratio * sin_theta > 1.0;
    Vector3d direction;

    if (cannot_refract || reflectance(cos_theta, refraction_ratio) > randomDouble())
        direction = reflect(unit_direction, rec.normal_);
    else
        direction = refract(unit_direction, rec.normal_, refraction_ratio);

    scattered = Ray(rec.p_, direction, rayIn.time());

    Vector3d refracted = refract(unit_direction, rec.normal_, refraction_ratio);

    scattered = Ray(rec.p_, refracted);
    return true;
}

double Dielectric::reflectance(double cosine, double ref_idx) {
    // Use Schlick's approximation for reflectance.
    auto r0 = (1-ref_idx) / (1+ref_idx);
    r0 = r0*r0;
    return r0 + (1-r0)*pow((1 - cosine),5);
}