//
// Created by jaden on 12/20/2022.
//

#include "Texture.h"

SolidColor::SolidColor(Color3d c) {
    colorValue_ = c;
}

SolidColor::SolidColor(double red, double green, double blue) {
    SolidColor(Color3d(red, green, blue));
}

Color3d SolidColor::value(double u, double v, const Vector3d &p) const {
    return colorValue_;
}

CheckerTexture::CheckerTexture(shared_ptr<Texture> even, shared_ptr<Texture> odd) {
    even_ = even;
    odd_ = odd;
}

CheckerTexture::CheckerTexture(Color3d c1, Color3d c2) {
    even_ = make_shared<SolidColor>(c1);
    odd_ = make_shared<SolidColor>(c2);
}

Color3d CheckerTexture::value(double u, double v, const Vector3d &p) const {
    auto sines = sin(10*p.x())*sin(10*p.y())*sin(10*p.z());
    if (sines < 0)
        return odd_->value(u, v, p);
    else
        return even_->value(u, v, p);
}

NoiseTexture::NoiseTexture(double scale) {
    scale_ = scale;
}

Color3d NoiseTexture::value(double u, double v, const Point3d &p) const {
    return Color3d(1,1,1) * 0.5 * (1.0 + sin(scale_*p.z() +  10*noise_.turb(p)));
}