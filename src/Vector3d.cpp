//
// Created by jaden on 11/6/2022.
//

#include "Vector3d.h"

using std::sqrt;

Vector3d::Vector3d() {
    coords[0] = 0;
    coords[1] = 0;
    coords[2] = 0;
}

Vector3d::Vector3d(GLdouble c1, GLdouble c2, GLdouble c3) {
    coords[0] = c1;
    coords[1] = c2;
    coords[2] = c3;
}

Vector3d::~Vector3d() {

}

GLdouble Vector3d::x() const{
    return coords[0];
}

GLdouble Vector3d::y() const{
    return coords[1];
}

GLdouble Vector3d::z() const {
    return coords[2];
}

Vector3d Vector3d::operator-() const {
    return Vector3d(-coords[0], -coords[1], -coords[2]);
}

GLdouble Vector3d::operator[](int i) const {
    return coords[i];
}
GLdouble &Vector3d::operator[](int i) {
    return  coords[i];
}

Vector3d &Vector3d::operator+=(const Vector3d &v) {
    coords[0] += v[0];
    coords[1] += v[1];
    coords[2] += v[2];
    return *this;
}

Vector3d &Vector3d::operator*=(const GLdouble t) {
    coords[0] *= t;
    coords[1] *= t;
    coords[2] *= t;
    return *this;
}

Vector3d &Vector3d::operator/=(const GLdouble t) {
    return *this *= 1/t;
}

GLdouble Vector3d::length() const {
    return sqrt(length_squared());
}

GLdouble Vector3d::length_squared() const {
    return coords[0]*coords[0] + coords[1]*coords[1] + coords[2]*coords[2];
}

