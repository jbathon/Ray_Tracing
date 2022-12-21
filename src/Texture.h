//
// Created by jaden on 12/20/2022.
//

#ifndef RAY_TRACING_TEXTURE_H
#define RAY_TRACING_TEXTURE_H

#include "Utilities.h"
#include "Perlin.h"

class Texture {
public:
    virtual Color3d value(double u, double v, const Point3d &p) const = 0;
};

class SolidColor : public Texture {
public:
    SolidColor() {}
    SolidColor(Color3d c);
    SolidColor(double red, double green, double blue);

    virtual Color3d value(double u, double v, const Vector3d &p) const override;

private:
    Color3d colorValue_;
};

class CheckerTexture : public Texture {
public:
    CheckerTexture() {}

    CheckerTexture(shared_ptr<Texture> even, shared_ptr<Texture> odd);

    CheckerTexture(Color3d c1, Color3d c2);

    virtual Color3d value(double u, double v, const Point3d& p) const override;

private:
    shared_ptr<Texture> odd_;
    shared_ptr<Texture> even_;
};

class NoiseTexture : public Texture {
    public:
        NoiseTexture() {}
        NoiseTexture(double scale);

        virtual Color3d value(double u, double v, const Point3d& p) const override;

    private:
        Perlin noise_;
        double scale_;
};

#endif //RAY_TRACING_TEXTURE_H
