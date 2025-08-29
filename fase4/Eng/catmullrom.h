#ifndef CATMULL_ROM_H
#define CATMULL_ROM_H

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <stdlib.h>
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

void buildRotMatrix(float *, float *, float *, float *);

void cross(float *, float *, float *);

void normalize(float *);

void multMatrixVector(float [4][4], float *, float *);

void getCatmullRomPoint(float , float *, float *, float *, float *, float *, float *);

void getGlobalCatmullRomPoint(float , float *, float *,std::vector<std::vector<float>>);

void renderCatmullRomCurve(float* , float* , std::vector<std::vector<float>>, float);



#endif
