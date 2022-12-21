//
// Created by jaden on 12/12/2022.
//

#ifndef RAY_TRACING_CAMERA_H
#define RAY_TRACING_CAMERA_H

#include "Utilities.h"

class Camera {
    private:
        Point3d origin_;
        Point3d lowerLeftCorner_;
        Vector3d horizontal_;
        Vector3d vertical_;
        Vector3d u, v, w;
        double lensRadius;
        double time0_;
        double time1_;
    public:
        Camera(Point3d lookfrom,
               Point3d lookat,
               Vector3d   vup,
               double vfov, // vertical field-of-view in degrees
               double aspect_ratio,
               double aperture,
               double focus_dist,
               double time0 = 0,
               double time1 = 0);
        Ray getRay(double s, double t) const;

};


#endif //RAY_TRACING_CAMERA_H
