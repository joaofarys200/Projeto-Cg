#define _USE_MATH_DEFINES
#include "functions.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <cmath>
#include <math.h>



void plane(float unit, int slices, std::string ficheiro) {


    std::ofstream myfile(ficheiro);

    if (!myfile.is_open()) {
        return;
    }

    float comp = unit / slices;
    float offset = unit / 2;
    float x1, x2, z1, z2;

    for (int i = 0; i < slices; i++) {
        for (int j = 0; j < slices; j++) {
            x1 = i * comp - offset;
            z1 = j * comp - offset;
            x2 = (i+1) * comp - offset;
            z2 = (j+1) * comp - offset;

            myfile << x1 << ' ' << 0.0f << ' ' << z1 << '\n';
            myfile << x2 << ' ' << 0.0f << ' ' << z2 << '\n';
            myfile << x2 << ' ' << 0.0f << ' ' << z1 << '\n';

            myfile << x1 << ' ' << 0.0f << ' ' << z1 << '\n';
            myfile << x1 << ' ' << 0.0f << ' ' << z2 << '\n';
            myfile << x2 << ' ' << 0.0f << ' ' << z2 << '\n';
        }
    }
    myfile.close();
}


void box(float unit, int slices, std::string ficheiro){
 

    std::ofstream myfile(ficheiro);

    if (!myfile.is_open()) {
        return;
    }

    float comp = unit / slices;
    float offset = unit / 2;
    float x1, x2, y1, y2, z1, z2;

    for (int i = 0; i < slices; i++) {
        for (int j = 0; j < slices; j++) {
            x1 = i * comp - offset;
            z1 = j * comp - offset;
            x2 = (i+1) * comp - offset;
            z2 = (j+1) * comp - offset;

            myfile << x1 << ' ' << offset << ' ' << z1 << '\n';
            myfile << x2 << ' ' << offset << ' ' << z2 << '\n';
            myfile << x2 << ' ' << offset << ' ' << z1 << '\n';

            myfile << x1 << ' ' << offset << ' ' << z1 << '\n';
            myfile << x1 << ' ' << offset << ' ' << z2 << '\n';
            myfile << x2 << ' ' << offset << ' ' << z2 << '\n';

            myfile << x2 << ' ' << -offset << ' ' << z2 << '\n';
            myfile << x1 << ' ' << -offset << ' ' << z1 << '\n';
            myfile << x2 << ' ' << -offset << ' ' << z1 << '\n';

            myfile << x1 << ' ' << -offset << ' ' << z2 << '\n';
            myfile << x1 << ' ' << -offset << ' ' << z1 << '\n';
            myfile << x2 << ' ' << -offset << ' ' << z2 << '\n';
        }
    }

    for (int i = 0; i< slices; i++) {
        for (int j = 0; j < slices; j++) {
            x1 = i * comp - offset;
            y1 = j * comp - offset;
            x2 = (i+1) * comp - offset;
            y2 = (j+1) * comp - offset;

            myfile << x2 << ' ' << y2 << ' ' << offset << '\n';
            myfile << x1 << ' ' << y1 << ' ' << offset << '\n';
            myfile << x2 << ' ' << y1 << ' ' << offset << '\n';

            myfile << x1 << ' ' << y2 << ' ' << offset << '\n';
            myfile << x1 << ' ' << y1 << ' ' << offset << '\n';
            myfile << x2 << ' ' << y2 << ' ' << offset << '\n';

            myfile << x1 << ' ' << y1 << ' ' << -offset << '\n';
            myfile << x2 << ' ' << y2 << ' ' << -offset << '\n';
            myfile << x2 << ' ' << y1 << ' ' << -offset << '\n';

            myfile << x1 << ' ' << y1 << ' ' << -offset << '\n';
            myfile << x1 << ' ' << y2 << ' ' << -offset << '\n';
            myfile << x2 << ' ' << y2 << ' ' << -offset << '\n';
        }
    }

    for (int i = 0; i< slices; i++) {
        for (int j = 0; j < slices; j++) {
            z1 = i * comp - offset;
            y1 = j * comp - offset;
            z2 = (i+1) * comp - offset;
            y2 = (j+1) * comp - offset;

            myfile << offset << ' ' << y1 << ' ' << z1 << '\n';
            myfile << offset << ' ' << y2 << ' ' << z2 << '\n';
            myfile << offset << ' ' << y1 << ' ' << z2 << '\n';

            myfile << offset << ' ' << y1 << ' ' << z1 << '\n';
            myfile << offset << ' ' << y2 << ' ' << z1 << '\n';
            myfile << offset << ' ' << y2 << ' ' << z2 << '\n';

            myfile << -offset << ' ' << y2 << ' ' << z2 << '\n';
            myfile << -offset << ' ' << y1 << ' ' << z1 << '\n';
            myfile << -offset << ' ' << y1 << ' ' << z2 << '\n';

            myfile << -offset << ' ' << y2 << ' ' << z1 << '\n';
            myfile << -offset << ' ' << y1 << ' ' << z1 << '\n';
            myfile << -offset << ' ' << y2 << ' ' << z2 << '\n';
        }
    }

    myfile.close();

}


void cone(float radius, float height, int slices, int stacks, std::string ficheiro){


    std::ofstream myfile(ficheiro);

    if (!myfile.is_open()) {
        return;
    }


    float arch_alfa = 2*static_cast<float>(M_PI) / slices;
    float ratio = height/radius;
    float stack_size = height/stacks;
    float x1, x2, x3, x4, y1, y2, z1, z2, z3, z4, h1, h2, r1, r2;

    
    for (int i = 0; i < slices; i++) {
        x1 = radius * sin(arch_alfa * i);
        x2 = radius * sin(arch_alfa * (i+1));
        z1 = radius * cos(arch_alfa * i);
        z2 = radius * cos(arch_alfa * (i+1));
     
        myfile << x1 << ' ' << 0.0f << ' ' << z1 << '\n';
        myfile << 0.0f << ' ' << 0.0f << ' ' << 0.0f << '\n';
        myfile << x2 << ' ' << 0.0f << ' ' << z2 << '\n';
    }

    for (int i = 0; i < stacks; i++) {
        for (int j = 0; j < slices; j++) {
            h1 = height - (i * stack_size);
            h2 = height - ((i+1) * stack_size);
            r1 = h1 / ratio;
            r2 = h2 / ratio;

            x1 = r1 * sin(arch_alfa * j);
            x2 = r1 * sin(arch_alfa * (j+1));
            x3 = r2 * sin(arch_alfa * (j+1));
            x4 = r2 * sin(arch_alfa * j);
            y1 = (i * stack_size);
            y2 = (i+1) * stack_size;
            z1 = r1 * cos(arch_alfa * j);
            z2 = r1 * cos(arch_alfa * (j+1));
            z3 = r2 * cos(arch_alfa * (j+1));
            z4 = r2 * cos(arch_alfa * j);
  
            myfile << x1 << ' ' << y1 << ' ' << z1 << '\n';
            myfile << x2 << ' ' << y1 << ' ' << z2 << '\n';
            myfile << x4 << ' ' << y2 << ' ' << z4 << '\n';

            if (j != slices - 1) {
                
                myfile << x4 << ' ' << y2 << ' ' << z4 << '\n';
                myfile << x2 << ' ' << y1 << ' ' << z2 << '\n';
                myfile << x3 << ' ' << y2 << ' ' << z3 << '\n';
            }            
        }
    }

   myfile.close();
}



void sphere(float radius, int slices, int stacks, std::string ficheiro) {


    std::ofstream myfile(ficheiro);

    if (!myfile.is_open()) {
        return;
    }

    float j = (2 * static_cast<float>( M_PI))/slices;

    float t=(static_cast<float>(stacks) /2)-1;

    float l= static_cast<float>(M_PI) /stacks;
    
    for(float i = 0.0f; i<2*M_PI; i+=j){

        myfile << 0.0f << " " << radius << " " << 0.0f << "\n";
        myfile << radius*cos(l*t)*sin(i) << " " << radius*sin(l*t) << " " << radius*cos(l*t)*cos(i) << "\n";
        myfile << radius*cos(l*t)*sin(i+j) << " " << radius*sin(l*t) << " " << radius*cos(l*t)*cos(i+j) << "\n";

        myfile << (0.0f) << " " << radius << " " << (0.0f) << "\n";
        myfile << radius*cos(l*t)*sin(i) << " " << radius*sin(l*t) << " " << radius*cos(l*t)*cos(i) << "\n";
        myfile << radius*cos(l*t)*sin(i+j) << " " << radius*sin(l*t) << " " << radius*cos(l*t)*cos(i+j) << "\n";

        myfile << (0.0f) << " " << -radius << " " << (0.0f) << "\n";
        myfile << radius*cos(l*t)*sin(i+j) << " " << -radius*sin(l*t) << " " <<radius*cos(l*t)*cos(i+j) << "\n";
        myfile << radius*cos(l*t)*sin(i) << " " << -radius*sin(l*t) << " " << radius*cos(l*t)*cos(i) << "\n";

    }


    for(float n=l*t;n>-(l*t);n-=l) {

        for (float i = 0.0f; i < 2 * M_PI; i += j) {

            myfile << radius * cos(n) * sin(i) << " " <<  radius * sin(n) << " " << radius * cos(n) * cos(i) << "\n";
            myfile << radius * cos(n-l) * sin(i + j) << " " << radius * sin(n-l) << " " << radius * cos(n-l) * cos(i + j) << "\n";
            myfile <<  radius * cos(n) * sin(i + j) << " " << radius * sin(n) << " " << radius * cos(n) * cos(i + j) << "\n";
            
            myfile << radius * cos(n) * sin(i) << " " << radius * sin(n) << " " <<  radius * cos(n) * cos(i)<< "\n";
            myfile << radius * cos(n-l) * sin(i) << " " << radius * sin(n-l) << " " << radius * cos(n-l) * cos(i) << "\n";
            myfile << radius * cos(n-l) * sin(i+j) << " " << radius * sin(n-l) << " " << radius * cos(n-l) * cos(i+j) << "\n";



        }
    }

    myfile.close();
}


void torus(float max_radius, float min_radius, int slices, int stacks, std::string ficheiro) {

    std::ofstream myfile(ficheiro);

    if (!myfile.is_open()) {
        return;
    }

    float arch_alpha = (2 * M_PI) / stacks, arch_beta = (2 * M_PI) / slices;
    float x1, x2, x3, x4, y1, y2, y3, y4, z1, z2, z3, z4;

    max_radius = (max_radius + min_radius) / 2;
    min_radius = max_radius - min_radius;


    for (int i = 0; i < stacks; i++) {
        for (int j = 0; j < slices; j++) {
            x1 = (max_radius + min_radius * cos(arch_alpha * i)) * cos(arch_beta * j);
            x2 = (max_radius + min_radius * cos(arch_alpha * (i+1))) * cos(arch_beta * j);
            x3 = (max_radius + min_radius * cos(arch_alpha * (i+1))) * cos(arch_beta * (j+1));
            x4 = (max_radius + min_radius * cos(arch_alpha * i)) * cos(arch_beta * (j+1));

            y1 = min_radius * sin(arch_alpha * i);
            y2 = min_radius * sin(arch_alpha * (i+1));
            y3 = min_radius * sin(arch_alpha * (i+1));
            y4 = min_radius * sin(arch_alpha * i);

            z1 = (max_radius + min_radius * cos(arch_alpha * i)) * sin(arch_beta * j);
            z2 = (max_radius + min_radius * cos(arch_alpha * (i+1))) * sin(arch_beta * j);
            z3 = (max_radius + min_radius * cos(arch_alpha * (i+1))) * sin(arch_beta * (j+1));
            z4 = (max_radius + min_radius * cos(arch_alpha * i)) * sin(arch_beta * (j+1));

            // Write vertices to file
            myfile << x1 << ' ' << y1 << ' ' << z1 << '\n';
            myfile << x2 << ' ' << y2 << ' ' << z2 << '\n';
            myfile << x4 << ' ' << y4 << ' ' << z4 << '\n';

            myfile << x2 << ' ' << y2 << ' ' << z2 << '\n';
            myfile << x3 << ' ' << y3 << ' ' << z3 << '\n';
            myfile << x4 << ' ' << y4 << ' ' << z4 << '\n';
        }
    }
    myfile.close();
}






std::vector<std::vector<std::vector<float>>> readPatchesFile(std::string patch) {

    std::vector<std::vector<int>> indexPatch;
    std::vector<std::vector<float>> controlPoints;

    const char* bpatch = patch.c_str();
    std::fstream file(bpatch);
    std::vector<std::vector<std::vector<float>>> ret;

    if (!file.is_open()) {
        return ret;
    }

    std::string line;

    // Leitura dos patches e do ponto de controlo
    for (int j = 0; j < 2; j++) {
        // Numero de patches/pontos de controlo (1a linha)
        if (!std::getline(file, line)) return ret;
        int n = std::stoi(line);

        // se j == 0, entao esta a ler os patches, se nao esta a ler os pontos de controlo
        for (int i = 0; i < n; i++) {
            if (!std::getline(file, line)) return ret;
            std::vector<int> index;
            std::vector<float> point;
            std::istringstream iss(line);
            std::string token;
            while (std::getline(iss, token, ',')) {
                if (j == 0) {
                    index.push_back(std::stoi(token));
                }
                else {
                    point.push_back(std::stof(token));
                }
            }
            if (j == 0) {
                indexPatch.push_back(index);
            }
            else {
                controlPoints.push_back(point);
            }
            
        }
    }

    for (std::vector<int> indexes : indexPatch) {
        std::vector<std::vector<float>> patch;
        for (int indexes : indexes) {
            patch.push_back(controlPoints[indexes]);
        }
        ret.push_back(patch);
    }
    file.close();

    return ret;
}


void multMatrixVector(float m[4][4], float *v, float *res) {

    for (int j = 0; j < 4; ++j) {
        res[j] = 0;
        for (int k = 0; k < 4; ++k) {
            res[j] += v[k] * m[j][k];
        }
    }

}

void multMatrixMatrix(float a[4][4], float b[4][4], float res[4][4]){
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++){
            res[i][j] = 0;
            for(int k = 0; k < 4; k++)
                res[i][j] += a[i][k] * b[k][j];
        }
}

float B(float U, float V, float m[4][4]){

    float aux[4];
    float v[4];
    float r;

    v[0] = powf(V,3);
    v[1] = powf(V,2);
    v[2] = V;
    v[3] = 1;

    multMatrixVector(m,v,aux);

    r = powf(U,3)*aux[0] + powf(U,2)*aux[1] + U*aux[2] + aux[3];

    return r;

}


std::string surface(float mx[4][4], float my[4][4], float mz[4][4], int tesselation){



    std::stringstream buffer;

    float x1, x2, x3, x4, y1, y2, y3, y4, z1, z2, z3, z4;
    float tesselation_level = 1.0/tesselation;

    for(float i=0; i<1; i+=tesselation_level){
        for(float j=0; j<1; j+=tesselation_level){

            x1 = B(i,j,mx);
            x2 = B(i+tesselation_level,j,mx);
            x3 = B(i+tesselation_level,j+tesselation_level,mx);
            x4 = B(i,j+tesselation_level,mx);

            y1 = B(i,j,my);
            y2 = B(i+tesselation_level,j,my);
            y3 = B(i+tesselation_level,j+tesselation_level,my);
            y4 = B(i,j+tesselation_level,my);

            z1 = B(i,j,mz);
            z2 = B(i+tesselation_level,j,mz);
            z3 = B(i+tesselation_level,j+tesselation_level,mz);
            z4 = B(i,j+tesselation_level,mz);

            
            buffer << x1 << ' ' << y1 << ' ' << z1 << '\n';
            
            buffer << x2 << ' ' << y2 << ' ' << z2 << '\n';

            buffer << x4 << ' ' << y4 << ' ' << z4 << '\n';
            
            
            buffer << x2 << ' ' << y2 << ' ' << z2 << '\n';

            buffer << x3 << ' ' << y3 << ' ' << z3 << '\n';

            
            buffer << x4 << ' ' << y4 << ' ' << z4 << '\n';
                        

        }

    }
    
    return buffer.str();

}




void bezier_patches(std::string patch, int tesselation, std::string ficheiro) {

    std::ofstream myfile(ficheiro);

    if (!myfile.is_open()) {
        return;
    }

    std::vector<std::vector<std::vector<float>>> patches = readPatchesFile(patch);

    float bezier[4][4]={
        {-1.0f, 3.0f, -3.0f, 1.0f},
        {3.0f, -6.0f, 3.0f, 0.0f},
        {-3.0f, 3.0f, 0.0f, 0.0f},
        {1.0f, 0.0f, 0.0f, 0.0f}
    };

    float mx[4][4];
    float my[4][4];
    float mz[4][4];
    float aux[4][4];


    for(int i =0; i<patches.size(); i++){
        int posi=0;
        int posj=0;

        for(int j=0; j<16; j++){

            mx[posj][posi]=patches[i][j][0];
            my[posj][posi]=patches[i][j][1];
            mz[posj][posi]=patches[i][j][2];

            posj++;
            if(j==3 || j==7 || j==11){
                posi++;
                posj=0;
            }
        }


        multMatrixMatrix(bezier, mx, aux);
        multMatrixMatrix(aux, bezier, mx);

        multMatrixMatrix(bezier, my, aux);
        multMatrixMatrix(aux, bezier, my);

        multMatrixMatrix(bezier, mz, aux);
        multMatrixMatrix(aux, bezier, mz);


        myfile << surface(mx,my,mz,tesselation);
    }

    myfile.close();
}









