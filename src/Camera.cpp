//
// Created by jaden on 12/12/2022.
//

#include "Camera.h"

Camera::Camera(Point3d lookfrom,
               Point3d lookat,
               Vector3d   vup,
               double vfov, // vertical field-of-view in degrees
               double aspect_ratio,
               double aperture,
               double focus_dist,
               double time0,
               double time1) {

        auto theta = degreesToRadians(vfov);
        auto h = tan(theta/2);
        auto viewport_height = 2.0 * h;
        auto viewport_width = aspect_ratio * viewport_height;

        auto aspectRatio = 16.0 / 9.0;
        auto viewportHeight = 2.0;
        auto viewportWidth = aspectRatio * viewportHeight;
        auto focalLength = 1.0;

        auto w = unitVector(lookfrom - lookat);
        auto u = unitVector(cross(vup, w));
        auto v = cross(w, u);

        origin_ = lookfrom;
        horizontal_ = focus_dist * viewport_width * u;
        vertical_ = focus_dist * viewport_height * v;
        lowerLeftCorner_ = origin_ - horizontal_/2 - vertical_/2 - focus_dist*w;

        lensRadius = aperture / 2;

        time0_ = time0;
        time1_ = time1;
}

Ray Camera::getRay(double s, double t) const{
    Vector3d rd = lensRadius * randomInUnitDisk();
    Vector3d offset = u * rd.x() + v * rd.y();

    return Ray(origin_ + offset,
               lowerLeftCorner_ + s*horizontal_ + t*vertical_ - origin_ - offset,
               randomDouble(time0_,time1_));
}