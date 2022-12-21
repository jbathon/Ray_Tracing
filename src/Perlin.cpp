//
// Created by jaden on 12/20/2022.
//

#include "Perlin.h"

Perlin::Perlin() {
    ranvec_ = new Vector3d[pointCount_];
    for (int i = 0; i < pointCount_; ++i) {
        ranvec_[i] = unitVector(Vector3d::random(-1,1));
    }

    permX_ = perlinGeneratePerm();
    permY_ = perlinGeneratePerm();
    permZ_ = perlinGeneratePerm();
}

Perlin::~Perlin() {
    delete[] ranvec_;
    delete[] permX_;
    delete[] permY_;
    delete[] permZ_;
}

double Perlin::noise(const Point3d &p) const {
    auto u = p.x() - floor(p.x());
    auto v = p.y() - floor(p.y());
    auto w = p.z() - floor(p.z());

    auto i = static_cast<int>(floor(p.x()));
    auto j = static_cast<int>(floor(p.y()));
    auto k = static_cast<int>(floor(p.z()));
    Vector3d c[2][2][2];

    for (int di=0; di < 2; di++)
        for (int dj=0; dj < 2; dj++)
            for (int dk=0; dk < 2; dk++)
                c[di][dj][dk] = ranvec_[
                        permX_[(i+di) & 255] ^
                        permY_[(j+dj) & 255] ^
                        permZ_[(k+dk) & 255]
                ];

    return perlinInterp(c, u, v, w);
}



int * Perlin::perlinGeneratePerm() {

    auto p = new int[pointCount_];

    for (int i = 0; i < Perlin::pointCount_; i++)
        p[i] = i;

    permute(p, pointCount_);

    return p;
}

void Perlin::permute(int *p, int n) {
    for (int i = n-1; i > 0; i--) {
        int target = randomInt(0, i);
        int tmp = p[i];
        p[i] = p[target];
        p[target] = tmp;
    }
}

double Perlin::trilinearInterp(double (*c)[2][2], double u, double v, double w) {
    auto accum = 0.0;
    for (int i=0; i < 2; i++)
        for (int j=0; j < 2; j++)
            for (int k=0; k < 2; k++)
                accum += (i*u + (1-i)*(1-u))*
                         (j*v + (1-j)*(1-v))*
                         (k*w + (1-k)*(1-w))*c[i][j][k];

    return accum;
}

double Perlin::perlinInterp(Vector3d (*c)[2][2], double u, double v, double w) {
    auto uu = u*u*(3-2*u);
    auto vv = v*v*(3-2*v);
    auto ww = w*w*(3-2*w);
    auto accum = 0.0;

    for (int i=0; i < 2; i++)
        for (int j=0; j < 2; j++)
            for (int k=0; k < 2; k++) {
                Vector3d weight_v(u-i, v-j, w-k);
                accum += (i*uu + (1-i)*(1-uu))
                         * (j*vv + (1-j)*(1-vv))
                         * (k*ww + (1-k)*(1-ww))
                         * dot(c[i][j][k], weight_v);
            }

    return accum;
}

double Perlin::turb(const Point3d &p, int depth) const {
    auto accum = 0.0;
    auto temp_p = p;
    auto weight = 1.0;

    for (int i = 0; i < depth; i++) {
        accum += weight*noise(temp_p);
        weight *= 0.5;
        temp_p *= 2;
    }

    return fabs(accum);
}