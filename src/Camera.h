//
// Created by jaden on 12/12/2022.
//

#ifndef RAY_TRACING_CAMERA_H
#define RAY_TRACING_CAMERA_H

#include "ray.h"

class Camera {
    private:
        Point3d origin_;
        Point3d lowerLeftCorner_;
        Vector3d horizontal_;
        Vector3d vertical_;
    public:
        Camera();
        Ray getRay(double u, double v);

};


#endif //RAY_TRACING_CAMERA_H
