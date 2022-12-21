//
// Created by jaden on 12/20/2022.
//

#ifndef RAY_TRACING_DIFFUSELIGHT_H
#define RAY_TRACING_DIFFUSELIGHT_H

#include "Utilities.h"
#include "Material.h"
#include "Texture.h"

class DiffuseLight : public Material {
public:
    DiffuseLight(shared_ptr<Texture> a) : emit_(a) {}
    DiffuseLight(Color3d c) : emit_(make_shared<SolidColor>(c)) {}

    virtual bool scatter(
            const Ray& rayIn, const HitRecord& rec, Color3d& attenuation, Ray& scattered
    )  const override;

    virtual Color3d emitted(double u, double v, const Point3d& p) const override;

public:
    shared_ptr<Texture> emit_;
};


#endif //RAY_TRACING_DIFFUSELIGHT_H
