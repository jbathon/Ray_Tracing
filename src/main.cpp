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
#include "MovingSphere.h"
#include "DiffuseLight.h"
#include "Rectangle.h"
#include "Box.h"
#include "Rotation.h"
#include "Translate.h"


/**** Image Globals****/
auto aspect_ratio = 1.0 / 1.0;
int width = 600;
const int height = static_cast<int>(width / aspect_ratio);
int samplesPerPixel = 200; //500
const int maxDepth = 50; //50
double xOffset = 0;
double yOffset = 0;


PPM ppm(width, height);



Color3d rayColor(const Ray& ray,const Color3d& background, const HittableInterface& world, int depth) {
    HitRecord rec;

    if (depth <= 0)
        return Color3d(0,0,0);

    // If the ray hits nothing, return the background color.
    if (!world.hit(ray, 0.001, infinity, rec))
        return background;

    Ray scattered;
    Color3d attenuation;
    Color3d emitted = rec.matPtr_->emitted(rec.u_, rec.v_, rec.p_);

    if (!rec.matPtr_->scatter(ray, rec, attenuation, scattered))
        return emitted;

    return emitted + attenuation * rayColor(scattered, background, world, depth-1);
}


void display() {
    // Sets pixels to default values
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_POINTS);
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            Color3d color = ppm.at(j, i).limitToRange(0, 0.999);

            auto r = color.x();
            auto g = color.y();
            auto b = color.z();


            glColor3d(
                    static_cast<int>(256 * color.x()) ,
                    static_cast<int>(256 * color.y()) ,
                    static_cast<int>(256 * color.z())
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

    auto checker = make_shared<CheckerTexture>(Color3d(0.2, 0.3, 0.1), Color3d(0.9, 0.9, 0.9));
    world.add(make_shared<Sphere>(Point3d(0,-1000,0), 1000, make_shared<Lambertian>(checker)));

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
                    auto center2 = center + Vector3d(0, randomDouble(0,.5), 0);
                    world.add(make_shared<MovingSphere>(
                            center, center2, 0.0, 1.0, 0.2, sphere_material));
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

HittableList two_spheres() {
    HittableList objects;

    auto checker = make_shared<CheckerTexture>(Color3d(0.2, 0.3, 0.1), Color3d(0.9, 0.9, 0.9));

    objects.add(make_shared<Sphere>(Point3d(0,-10, 0), 10, make_shared<Lambertian>(checker)));
    objects.add(make_shared<Sphere>(Point3d(0, 10, 0), 10, make_shared<Lambertian>(checker)));

    return objects;
}

HittableList two_perlin_spheres() {
    HittableList objects;

    auto pertext = make_shared<NoiseTexture>(4);
    objects.add(make_shared<Sphere>(Point3d(0,-1000,0), 1000, make_shared<Lambertian>(pertext)));
    objects.add(make_shared<Sphere>(Point3d(0, 2, 0), 2, make_shared<Lambertian>(pertext)));

    return objects;
}

HittableList cornell_box() {
    HittableList objects;


    // Walls
    auto gold = make_shared<Lambertian>(Color3d(.855, .66, 0.0));
    auto white = make_shared<Lambertian>(Color3d(.73, .73, .73));
    auto purple = make_shared<Lambertian>(Color3d(.18, .102, .278));
    auto light = make_shared<DiffuseLight>(Color3d(15, 15, 15));
    auto checker = make_shared<CheckerTexture>(Color3d(0.0, 0.0, 0.0), Color3d(0.9, 0.9, 0.9));
    auto floor = make_shared<Lambertian>(checker);
    auto metal = make_shared<Metal>(Color3d(0.7, 0.6, 0.5), 0.0);

    objects.add(make_shared<YZRect>(0, 555, 0, 555, 555, purple));
    objects.add(make_shared<YZRect>(0, 555, 0, 555, 0, gold));
    objects.add(make_shared<XZRect>(213, 343, 227, 332, 554, light));
    objects.add(make_shared<XZRect>(0, 555, 0, 555, 0, floor));
    objects.add(make_shared<XZRect>(0, 555, 0, 555, 555, white));
    objects.add(make_shared<XYRect>(0, 555, 0, 555, 555, white));

    // Box 1
    shared_ptr<HittableInterface> box1 = make_shared<Box>(Point3d(0, 0, 0), Point3d(165, 330, 165), white);
    box1 = make_shared<RotateY>(box1, 15);
    box1 = make_shared<Translate>(box1, Vector3d(265,0,295));
    objects.add(box1);


    // Box 2
    shared_ptr<HittableInterface> sphere1 = make_shared<Sphere>(Point3d(190, 90, 190), 90, metal);
    objects.add(sphere1);

    return objects;
}

int main(int argc, char **argv) {

    // HittableList
    HittableList world = cornell_box();
    Color3d background(0,0,0);



    // Camera
    Point3d lookfrom(278, 278, -800);
    Point3d lookat(278, 278, 0);
    Vector3d vup(0, 1, 0);
    auto dist_to_focus = 10.0;
    auto aperture = 0.0;
    auto vfov = 40.0;
    auto time0 = 0.0;
    auto time1 = 1.0;

    Camera cam(lookfrom, lookat, vup, vfov, aspect_ratio, aperture, dist_to_focus,time0,time1);


    // Render

    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            Color3d pixelColor(0, 0, 0);
            #pragma omp parallel for
            for (int s = 0; s < samplesPerPixel; s++) {
                auto u = (double(i) + randomDouble()) / (width-1);
                auto v = (double(j) + randomDouble()) / (height-1);
                Ray ray = cam.getRay(u, v);
                pixelColor += rayColor(ray, background, world, maxDepth);
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
