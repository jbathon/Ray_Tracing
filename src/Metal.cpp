//
// Created by jaden on 12/20/2022.
//

#include "Metal.h"

bool Metal::scatter(const Ray &rayIn, const HitRecord &rec, Color3d &attenuation, Ray &scattered) const {
    Vector3d reflected = reflect(unitVector(rayIn.direction()), rec.normal_);
    scattered = Ray(rec.p_, reflected + fuzz*randomInUnitSphere(), rayIn.time());
    attenuation = albedo;
    return (dot(scattered.direction(), rec.normal_) > 0);
}