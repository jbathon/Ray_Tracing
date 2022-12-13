//
// Created by jaden on 12/12/2022.
//

#include "Camera.h"

Camera::Camera() {
        auto aspectRatio = 16.0 / 9.0;
        auto viewportHeight = 2.0;
        auto viewportWidth = aspectRatio * viewportHeight;
        auto focalLength = 1.0;

        origin_ = Point3d(0, 0, 0);
        horizontal_ = Vector3d(viewportWidth, 0.0, 0.0);
        vertical_ = Vector3d(0.0, viewportHeight, 0.0);
        lowerLeftCorner_ = origin_ - horizontal_/2 - vertical_/2 - Vector3d(0, 0, focalLength);
}

Ray Camera::getRay(double u, double v) {
    return Ray(origin_, lowerLeftCorner_ + u*horizontal_ + v*vertical_ - origin_);
}