//
// Created by jaden on 12/12/2022.
//

#ifndef RAY_TRACING_UTILITIES_H
#define RAY_TRACING_UTILITIES_H

#include <cmath>
#include <limits>
#include <memory>
#include <cstdlib>

#include "Ray.h"
#include "Vector3d.h"


// Usings

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions

inline double degreesToRadians(double degrees) {
    return degrees * pi / 180.0;
}

inline double clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

inline double randomDouble() {
    // Returns a random real in [0,1).
    return rand() / (RAND_MAX + 1.0);
}

inline double randomDouble(double min, double max) {
    // Returns a random real in [min,max).
    return min + (max-min)*randomDouble();
}

inline int randomInt(int min, int max) {
    // Returns a random integer in [min,max].
    return static_cast<int>(randomDouble(min, max+1));
}

inline Vector3d randomInUnitDisk() {
    while (true) {
        auto p = Vector3d(randomDouble(-1,1), randomDouble(-1,1), 0);
        if (p.length_squared() >= 1) continue;
        return p;
    }
}

inline Vector3d randomUnitVector() {
    return unitVector(randomInUnitSphere());
}

inline Vector3d randomInHemisphere(const Vector3d& normal) {
    Vector3d inUnitSphere = randomInUnitSphere();
    if (dot(inUnitSphere,normal)>0.0){
        return inUnitSphere;
    }
    else {
        return  -inUnitSphere;
    }
}

inline Vector3d reflect(const Vector3d& v, const Vector3d& n) {
    return v - 2*dot(v,n)*n;
}

inline Vector3d refract(const Vector3d& uv, const Vector3d& n, double etai_over_etat) {
    auto cos_theta = fmin(dot(-uv, n), 1.0);
    Vector3d r_out_perp =  etai_over_etat * (uv + cos_theta*n);
    Vector3d r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.length_squared())) * n;
    return r_out_perp + r_out_parallel;
}



#endif //RAY_TRACING_UTILITIES_H
