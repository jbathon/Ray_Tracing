//
// Created by jaden on 11/10/2022.
//

#include "Sphere.h"

Sphere::Sphere(const Point3d& center, double radius) {
    this->center = center;
    this->radius = radius;
}

Sphere::~Sphere() {

}

Point3d &Sphere::getCenter() {
    return center;
}

bool Sphere::hit(const Ray& ray) {
    Vector3d oc = ray.origin() - center;
    auto a = dot(ray.direction(), ray.direction());
    auto b = 2.0 * dot(oc, ray.direction());
    auto c = dot(oc, oc) - radius*radius;
    auto discriminant = b*b - 4*a*c;
    return (discriminant > 0);
}