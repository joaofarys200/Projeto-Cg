#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <vector>
#include <fstream>

void plane(float, int, std::string);

void box(float, int, std::string);

void cone(float, float, int, int, std::string);

void sphere(float, int, int, std::string);

void torus(float, float, int, int, std::string);

void multMatrixVector(float, float, float);

void multMatrixMatrix(float, float, float);

std::vector<std::vector<std::vector<float>>> readPatchesFile(std::string);

float B(float, float, float);

std::string surface(float, float, float, int);

void bezier_patches(std::string, int, std::string);

#endif
