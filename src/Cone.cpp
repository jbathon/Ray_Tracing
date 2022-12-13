//
// Created by jaden on 11/10/2022.
//

#include "Cone.h"

Cone::Cone(const Point3d &apex, double radius, double height) {
    apex_ = apex;
    radius_ = radius;
    height_ = height;
    alpha_ = (radius_*radius_)/(height_*height_);
}

Cone::~Cone() {

}





double Cone::hit(const Ray &ray) {
    auto o = ray.origin(); //origin
    auto oSq = ray.origin() * ray.origin(); //origin squared
    auto dir = ray.direction(); // direction
    auto dirSq = ray.direction()*ray.direction(); // direction squared
    auto apexSquared = apex_*apex_; // apex squared
    auto a = oSq.x() + oSq.z() - alpha_ * oSq.y() + apexSquared.x() + apexSquared.z() - alpha_ * apexSquared.y();
    auto b = 2*(o.x()*dir.x()+o.z()*dir.z()-alpha_*o.y()*dir.y()-dir.x()*apex_.x()-dir.z()*apex_.z()-alpha_*dir.y()*apex_.y());
    auto c =  dirSq.x()+dirSq.z()-alpha_*dirSq.y();
    auto discriminant = b * b - 4 * a * c;
    auto temp = ray.at((-b - sqrt(discriminant) ) / (2.0*a));
    if (discriminant < 0) {
        return -1.0;
    } else {
//        std::cout << (-b - sqrt(discriminant) ) / (2.0*a) << std::endl;
        return (-b - sqrt(discriminant) ) / (2.0*a);
    }
}

//Point3d &Cone::getCenter() {
//    return center;
//}
//
//double Cone::getRadius() {
//    return radius;
//}
//
//double Cone::getHeight() {
//    return height;
//}