//
// Created by jaden on 12/20/2022.
//

#ifndef RAY_TRACING_LAMBERTIAN_H
#define RAY_TRACING_LAMBERTIAN_H

#include "Material.h"
#include "Texture.h"

class Lambertian : public Material {
    private:
        shared_ptr<Texture> albedo;
    public:
        Lambertian(const Color3d& a) : albedo(make_shared<SolidColor>(a)) {}
        Lambertian(shared_ptr<Texture> a) : albedo(a) {}

        virtual bool scatter(
                const Ray& rayIn, const HitRecord& rec, Color3d& attenuation, Ray& scattered
        )  const override;
};


#endif //RAY_TRACING_LAMBERTIAN_H
