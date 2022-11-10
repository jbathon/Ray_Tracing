#include "Ray.h"
#include "Vector3d.h"
#include "PPM.h"
#include "Sphere.h"


/**** Image Globals****/


Shape* s = new Sphere(Point3d(0, 0, -1), 0.5);

Color3d rayColor(const Ray& ray) {
    if (s->hit(ray)) {
        return Color3d(0, 1, 0);
    }
    Vector3d unit_direction = unit_vector(ray.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*Color3d(1.0, 1.0, 1.0) + t*Color3d(0.2, 0.2, 0.2);
}


int main() {

    const auto aspect_ratio = 16.0 / 9.0;
    const int img_width = 1280;
    const int img_height = static_cast<int>(img_width / aspect_ratio);

    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    auto origin = Point3d(0, 0, 0);
    auto horizontal = Vector3d(viewport_width, 0, 0);
    auto vertical = Vector3d(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal/2 - vertical/2 - Vector3d(0, 0, focal_length);


    PPM ppm(img_width, img_height);

    for (int j = img_height-1; j >= 0; j--) {
        for (int i = 0; i < img_width; i++) {
            auto u = double(i) / (img_width-1);
            auto v = double(j) / (img_height-1);
            Ray ray(origin, lower_left_corner + u*horizontal + v*vertical - origin);
            ppm.at(j,i) = rayColor(ray);
        }
    }

    ppm.save("images/","raytrace");

    return 0;

}
