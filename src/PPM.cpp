//
// Created by jaden on 11/8/2022.
//

#include "PPM.h"
#include <fstream>

PPM::PPM(int width, int height) {
    this->width = width;
    this->height = height;
    ppm = new Color3d[width*height];
}

int  PPM::getWidth() {
    return width;
}

int  PPM::getHeight() {
    return height;
}

Color3d& PPM::at(int row, int col) {
    return ppm[row*width+col];
}

void PPM::save(string path, string name) {
    std::ofstream img(path + name + ".ppm");
    img <<  "P3\n" << width << " " << height << "\n255\n";
    for (int j = height-1; j >= 0; j--) {
        for (int i = 0; i < width; i++) {
            writeColor(img, at(j,i));
        }
    }
    img.close();
}

void PPM::writeColor(std::ostream &out, Color3d color) {
    out << static_cast<int>(255.999 * color.x()) << ' '
        << static_cast<int>(255.999 * color.y()) << ' '
        << static_cast<int>(255.999 * color.z()) << '\n';
}

PPM::~PPM() {
    delete[] ppm;
}