//
// Created by jaden on 12/12/2022.
//

#ifndef RAY_TRACING_MATERIAL_H
#define RAY_TRACING_MATERIAL_H

#include "Utilities.h"
#include "HittableInterface.h"

struct HitRecord;

class Material {
public:
    virtual bool scatter(
            const Ray& rayIn, const HitRecord& rec, Color3d& attenuation, Ray& scattered
    ) const = 0;
};

#endif //RAY_TRACING_MATERIAL_H
