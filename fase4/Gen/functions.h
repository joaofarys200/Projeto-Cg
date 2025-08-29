#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <fstream>
#include <sstream>

void plane(float, int, std::string);

void box(float, int, std::string);

void cone(float, float, int, int, std::string);

void sphere(float, int, int, std::string);

void torus(float, float, int, int, std::string);

void multMatrixVector(float, float, float);

void multMatrixMatrix(float, float, float);

std::vector<std::vector<std::vector<float>>> readPatchesFile(std::string);

float B(float, float, float);

float derivU(float, float, float m);

float derivU(float, float, float);

void crossProd(float *, float *, float *);

void normalize(float *);

std::string surface(float, float, float, int);

void bezier_patches(std::string, int, std::string);

#endif
