//
// Created by jaden on 11/8/2022.
//

#ifndef OPENGL_RAY_TRACING_PPM_H
#define OPENGL_RAY_TRACING_PPM_H

#include "Vector3d.h"

using std::string;

class PPM {
private:
    Color3d* ppm;
    int width;
    int height;

    void writeColor(std::ostream &out, Color3d color);

public:
    PPM(int width, int height);

    ~PPM();

    int getWidth();
    int getHeight();

    Color3d& at(int row, int col);

    void save(string path, string name);
};


#endif //OPENGL_RAY_TRACING_PPM_H
