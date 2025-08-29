#define _USE_MATH_DEFINES
#include "functions.h"
#include <fstream>
#include <cmath>



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
