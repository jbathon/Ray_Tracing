#include <GL/gl.h>
#include <GL/freeglut.h>
#include "Utilities.h"
#include "HittableList.h"
#include "PPM.h"
#include <cmath>
#include <omp.h>
#include "Camera.h"
#include "Sphere.h"
#include "Material.h"
#include "Lambertian.h"
#include "Metal.h"
#include "Dielectric.h"


/**** Image Globals****/
const auto aspect_ratio = 16.0 / 9.0;
const int width = 1280;
const int height = static_cast<int>(width / aspect_ratio);
const int samplesPerPixel = 500;
const int maxDepth = 50;
double xOffset = 0;
double yOffset = 0;


PPM ppm(width, height);



Color3d rayColor(const Ray& ray, const HittableInterface& shape, int depth) {
    HitRecord rec;

    if (depth <= 0)
        return Color3d(0,0,0);

    if (shape.hit(ray,0,infinity, rec)) {
        Ray scattered;
        Color3d attenuation;
        if (rec.matPtr_->scatter(ray, rec, attenuation, scattered)) {
            return attenuation * rayColor(scattered, shape, depth-1);
        }

        return Color3d(0,0,0);
    }
    Vector3d unitDirection = unitVector(ray.direction());
    auto t = 0.5*(unitDirection.y() + 1.0);
    return (1.0-t)*Color3d(1.0, 1.0, 1.0) + t*Color3d(0.5, 0.7, 1.0);
}


void display() {
    // Sets pixels to default values
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_POINTS);
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            Color3d color = ppm.at(j, i).limitToRange(0, 0.999);

            glColor3ub(
                    static_cast<int>(256 * color.x()),
                    static_cast<int>(256 * color.x()),
                    static_cast<int>(256 * color.x())
            );
            glVertex2i(i+xOffset, height-j+yOffset);
        }
    }
    glEnd();
    glutSwapBuffers();
    glFlush();
}

void idle(void) {
}

void init() {

    // Setting the default color of the window
    glClearColor(0, 0, 0, 0.0);

    // Setting window defaults
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, height, width, 0, -1.0, 1.0);
}

void reshape(int w, int h) {
    glViewport(0,0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, w, h, 0, -1.0, 1.0);
    xOffset = (w-width >= 0) ? (w-width)/2 : 0;
    yOffset = (h-height >= 0) ? (h-height)/2 : 0;
    glutPostRedisplay();
}

HittableList random_scene() {
    HittableList world;

    auto ground_material = make_shared<Lambertian>(Color3d(0.5, 0.5, 0.5));
    world.add(make_shared<Sphere>(Point3d(0,-1000,0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = randomDouble();
            Point3d center(a + 0.9*randomDouble(), 0.2, b + 0.9*randomDouble());

            if ((center - Point3d(4, 0.2, 0)).length() > 0.9) {
                shared_ptr<Material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = Color3d::random() * Color3d::random();
                    sphere_material = make_shared<Lambertian>(albedo);
                    world.add(make_shared<Sphere>(center, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = Color3d::random(0.5, 1);
                    auto fuzz = randomDouble(0, 0.5);
                    sphere_material = make_shared<Metal>(albedo, fuzz);
                    world.add(make_shared<Sphere>(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = make_shared<Dielectric>(1.5);
                    world.add(make_shared<Sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = make_shared<Dielectric>(1.5);
    world.add(make_shared<Sphere>(Point3d(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<Lambertian>(Color3d(0.4, 0.2, 0.1));
    world.add(make_shared<Sphere>(Point3d(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<Metal>(Color3d(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<Sphere>(Point3d(4, 1, 0), 1.0, material3));

    return world;
}



int main(int argc, char **argv) {

    // HittableList
    auto world = random_scene();



    // Camera
    Point3d lookfrom(13,2,3);
    Point3d lookat(0,0,0);
    Vector3d vup(0,1,0);
    auto dist_to_focus = 10.0;
    auto aperture = 0.1;

    Camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus);


    // Render

    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            Color3d pixelColor(0, 0, 0);
            for (int s = 0; s < samplesPerPixel; s++) {
                auto u = (double(i) + randomDouble()) / (width-1);
                auto v = (double(j) + randomDouble()) / (height-1);
                Ray ray = cam.getRay(u, v);
                pixelColor += rayColor(ray, world, maxDepth);
            }

            pixelColor /= samplesPerPixel;
            pixelColor = sqrt(pixelColor);
            ppm.at(j, i) = pixelColor;
        }
    }


    ppm.save("images/","raytrace");

    // Open GL
    glutInit(&argc, argv);

    /* we got a RGBA buffer and we're double buffering! */
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

    /* set some size for the window. */
    glutInitWindowSize(width, height);

    /* arbitrarily set an initial window position... */
    glutInitWindowPosition(100, 100);

    /* make the window.  give it a cool title */
    glutCreateWindow("Raytracing");

    init();

    /* set the callback functions */
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);

    /* start it! */
    glutMainLoop();

    return 0;

}
