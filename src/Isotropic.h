//
// Created by jaden on 12/20/2022.
//

#ifndef RAY_TRACING_ISOTROPIC_H
#define RAY_TRACING_ISOTROPIC_H

#include "Material.h"
#include "Texture.h"

class Isotropic : public Material {
    public:
        Isotropic(Color3d c) : albedo(make_shared<SolidColor>(c)) {}
        Isotropic(shared_ptr<Texture> a) : albedo(a) {}

        virtual bool scatter(
                const Ray& rayIn, const HitRecord& rec, Color3d& attenuation, Ray& scattered
        )  const override;

    private:
        shared_ptr<Texture> albedo;
};


#endif //RAY_TRACING_ISOTROPIC_H
