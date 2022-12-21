//
// Created by jaden on 12/20/2022.
//

#ifndef RAY_TRACING_PERLIN_H
#define RAY_TRACING_PERLIN_H

#include "Utilities.h"

class Perlin {
public:
    Perlin();
    ~Perlin();

    double noise(const Point3d& p) const;
    double turb(const Point3d& p, int depth=7) const;

private:
    static const int pointCount_ = 256;
    Vector3d* ranvec_;
    int* permX_;
    int* permY_;
    int* permZ_;


    static int* perlinGeneratePerm();


    static void permute(int* p, int n);
    static double trilinearInterp(double c[2][2][2], double u, double v, double w);
    static double perlinInterp(Vector3d c[2][2][2], double u, double v, double w);

};


#endif //RAY_TRACING_PERLIN_H
