#include "functions.h"



void normalize(float *a) {
    float l = sqrt(a[0]*a[0] + a[1] * a[1] + a[2] * a[2]);
    if(l!=0){
        a[0] = a[0]/l;
        a[1] = a[1]/l;
        a[2] = a[2]/l;
    }
}

void plane(float unit, int slices, std::string ficheiro) {


    std::ofstream myfile(ficheiro);

    if (!myfile.is_open()) {
        return;
    }

    float comp = unit / slices;
    float offset = unit / 2;
    float x1, x2, z1, z2;
    float text = 1.0f / slices;

    for (int i = 0; i < slices; i++) {
        for (int j = 0; j < slices; j++) {
            x1 = i * comp - offset;
            z1 = j * comp - offset;
            x2 = (i+1) * comp - offset;
            z2 = (j+1) * comp - offset;

            myfile << x1 << ' ' << 0.0f << ' ' << z1 << ' ';
            myfile << 0.0f << ' ' << 1.0f << ' ' << 0.0f << ' ';
            myfile << i*text << ' ' << j*text << '\n';

            myfile << x2 << ' ' << 0.0f << ' ' << z2 << ' ';
            myfile << 0.0f << ' ' << 1.0f << ' ' << 0.0f << ' ';
            myfile << (i+1)*text << ' ' << (j+1)*text << '\n';

            myfile << x2 << ' ' << 0.0f << ' ' << z1 << ' ';
            myfile << 0.0f << ' ' << 1.0f << ' ' << 0.0f << ' ';
            myfile << (i+1)*text << ' ' << j*text << '\n';

            myfile << x1 << ' ' << 0.0f << ' ' << z1 << ' ';
            myfile << 0.0f << ' ' << 1.0f << ' ' << 0.0f << ' ';
            myfile << i*text << ' ' << j*text << '\n';

            myfile << x1 << ' ' << 0.0f << ' ' << z2 << ' ';
            myfile << 0.0f << ' ' << 1.0f << ' ' << 0.0f << ' ';
            myfile << i*text << ' ' << (j+1)*text << '\n';

            myfile << x2 << ' ' << 0.0f << ' ' << z2 << ' ';
            myfile << 0.0f << ' ' << 1.0f << ' ' << 0.0f << ' ';
            myfile << (i+1)*text<< ' ' << (j+1)*text<< '\n';
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
    float x1, x2, y1, y2, z1, z2, tx1, tx2, tz1, tz2;
    float text = 1.0f / slices;

    for (int i = 0; i < slices; i++) {
        for (int j = 0; j < slices; j++) {
            x1 = i * comp - offset;
            z1 = j * comp - offset;
            x2 = (i+1) * comp - offset;
            z2 = (j+1) * comp - offset;
            tx1 = i*text;
            tx2 = (i+1)*text;
            tz1 = j*text;
            tz2 = (j+1)*text;

            myfile << x1 << ' ' << offset << ' ' << z1 << ' ';
            myfile << 0.0f << ' ' << 1.0f << ' ' << 0.0f << ' ';
            myfile << tx1 << ' ' << tz1 << '\n';
            

            myfile << x2 << ' ' << offset << ' ' << z2 << ' ';
            myfile << 0.0f << ' ' << 1.0f << ' ' << 0.0f << ' ';
            myfile << tx2 << ' ' << tz2 << '\n';

            myfile << x2 << ' ' << offset << ' ' << z1 << ' ';
            myfile << 0.0f << ' ' << 1.0f << ' ' << 0.0f << ' ';
            myfile << tx2 << ' ' << tz1 << '\n';

            myfile << x1 << ' ' << offset << ' ' << z1 << ' ';
            myfile << 0.0f << ' ' << 1.0f << ' ' << 0.0f << ' ';
            myfile << tx1 << ' ' << tz1 << '\n';

            myfile << x1 << ' ' << offset << ' ' << z2 << ' ';
            myfile << 0.0f << ' ' << 1.0f << ' ' << 0.0f << ' ';
            myfile << tx1 << ' ' << tz2 << '\n';

            myfile << x2 << ' ' << offset << ' ' << z2 << ' ';
            myfile << 0.0f << ' ' << 1.0f << ' ' << 0.0f << ' ';
            myfile << tx2 << ' ' << tz2 << '\n';

            myfile << x2 << ' ' << -offset << ' ' << z2 << ' ';
            myfile << 0.0f << ' ' << -1.0f << ' ' << 0.0f << ' ';
            myfile << tx2 << ' ' << tz2 << '\n';

            myfile << x1 << ' ' << -offset << ' ' << z1 << ' ';
            myfile << 0.0f << ' ' << -1.0f << ' ' << 0.0f << ' ';
            myfile << tx1 << ' ' << tz1 << '\n';

            myfile << x2 << ' ' << -offset << ' ' << z1 << ' ';
            myfile << 0.0f << ' ' << -1.0f << ' ' << 0.0f << ' ';
            myfile << tx2 << ' ' << tz1 << '\n';

            myfile << x1 << ' ' << -offset << ' ' << z2 << ' ';
            myfile << 0.0f << ' ' << -1.0f << ' ' << 0.0f << ' ';
            myfile << tx1 << ' ' << tz2 << '\n';

            myfile << x1 << ' ' << -offset << ' ' << z1 << ' ';
            myfile << 0.0f << ' ' << -1.0f << ' ' << 0.0f << ' ';
            myfile << tx1 << ' ' << tz1 << '\n';

            myfile << x2 << ' ' << -offset << ' ' << z2 << ' ';
            myfile << 0.0f << ' ' << -1.0f << ' ' << 0.0f << ' ';
            myfile << tx2 << ' ' << tz2 << '\n';
        }
    }

    for (int i = 0; i< slices; i++) {
        for (int j = 0; j < slices; j++) {
            x1 = i * comp - offset;
            y1 = j * comp - offset;
            x2 = (i+1) * comp - offset;
            y2 = (j+1) * comp - offset;
            tx1 = i*text;
            tx2 = (i+1)*text;
            tz1 = j*text;
            tz2 = (j+1)*text;

            myfile << x2 << ' ' << y2 << ' ' << offset << ' ';
            myfile << 0.0f << ' ' << 0.0f << ' ' << 1.0f << ' ';
            myfile << tx2 << ' ' << tz2 << '\n';

            myfile << x1 << ' ' << y1 << ' ' << offset << ' ';
            myfile << 0.0f << ' ' << 0.0f << ' ' << 1.0f << ' ';
            myfile << tx1 << ' ' << tz1 << '\n';

            myfile << x2 << ' ' << y1 << ' ' << offset << ' ';
            myfile << 0.0f << ' ' << 0.0f << ' ' << 1.0f << ' ';
            myfile << tx2 << ' ' << tz1 << '\n';

            myfile << x1 << ' ' << y2 << ' ' << offset << ' ';
            myfile << 0.0f << ' ' << 0.0f << ' ' << 1.0f << ' ';
            myfile << tx1 << ' ' << tz2 << '\n';

            myfile << x1 << ' ' << y1 << ' ' << offset << ' ';
            myfile << 0.0f << ' ' << 0.0f << ' ' << 1.0f << ' ';
            myfile << tx1 << ' ' << tz1 << '\n';

            myfile << x2 << ' ' << y2 << ' ' << offset << ' ';
            myfile << 0.0f << ' ' << 0.0f << ' ' << 1.0f << ' ';
            myfile << tx2 << ' ' << tz2 << '\n';

            myfile << x1 << ' ' << y1 << ' ' << -offset << ' ';
            myfile << 0.0f << ' ' << 0.0f << ' ' << -1.0f << ' ';
            myfile << tx1 << ' ' << tz1 << '\n';

            myfile << x2 << ' ' << y2 << ' ' << -offset << ' ';
            myfile << 0.0f << ' ' << 0.0f << ' ' << -1.0f << ' ';
            myfile << tx2 << ' ' << tz2 << '\n';

            myfile << x2 << ' ' << y1 << ' ' << -offset << ' ';
            myfile << 0.0f << ' ' << 0.0f << ' ' << -1.0f << ' ';
            myfile << tx2 << ' ' << tz1 << '\n';


            myfile << x1 << ' ' << y1 << ' ' << -offset << ' ';
            myfile << 0.0f << ' ' << 0.0f << ' ' << -1.0f << ' ';
            myfile << tx1 << ' ' << tz1 << '\n';

            myfile << x1 << ' ' << y2 << ' ' << -offset << ' ';
            myfile << 0.0f << ' ' << 0.0f << ' ' << -1.0f << ' ';
            myfile << tx1 << ' ' << tz2 << '\n';

            myfile << x2 << ' ' << y2 << ' ' << -offset << ' ';
            myfile << 0.0f << ' ' << 0.0f << ' ' << -1.0f << ' ';
            myfile << tx2 << ' ' << tz2 << '\n';
        }
    }

    for (int i = 0; i< slices; i++) {
        for (int j = 0; j < slices; j++) {
            z1 = i * comp - offset;
            y1 = j * comp - offset;
            z2 = (i+1) * comp - offset;
            y2 = (j+1) * comp - offset;
            tx1 = i*text;
            tx2 = (i+1)*text;
            tz1 = j*text;
            tz2 = (j+1)*text;

            myfile << offset << ' ' << y1 << ' ' << z1 << ' ';
            myfile << 1.0f << ' ' << 0.0f << ' ' << 0.0f << ' ';
            myfile << tx1 << ' ' << tz1 << '\n';

            myfile << offset << ' ' << y2 << ' ' << z2 << ' ';
            myfile << 1.0f << ' ' << 0.0f << ' ' << 0.0f << ' ';
            myfile << tx2 << ' ' << tz2 << '\n';

            myfile << offset << ' ' << y1 << ' ' << z2 << ' ';
            myfile << 1.0f << ' ' << 0.0f << ' ' << 0.0f << ' ';
            myfile << tx2 << ' ' << tz1 << '\n';

            myfile << offset << ' ' << y1 << ' ' << z1 << ' ';
            myfile << 1.0f << ' ' << 0.0f << ' ' << 0.0f << ' ';
            myfile << tx1 << ' ' << tz1 << '\n';

            myfile << offset << ' ' << y2 << ' ' << z1 << ' ';
            myfile << 1.0f << ' ' << 0.0f << ' ' << 0.0f << ' ';
            myfile << tx1 << ' ' << tz2 << '\n';

            myfile << offset << ' ' << y2 << ' ' << z2 << ' ';
            myfile << 1.0f << ' ' << 0.0f << ' ' << 0.0f << ' ';
            myfile << tx2 << ' ' << tz2 << '\n';

            myfile << -offset << ' ' << y2 << ' ' << z2 << ' ';
            myfile << -1.0f << ' ' << 0.0f << ' ' << 0.0f << ' ';
            myfile << tx2 << ' ' << tz2 << '\n';

            myfile << -offset << ' ' << y1 << ' ' << z1 << ' ';
            myfile << -1.0f << ' ' << 0.0f << ' ' << 0.0f << ' ';
            myfile << tx1 << ' ' << tz1 << '\n';

            myfile << -offset << ' ' << y1 << ' ' << z2 << ' ';
            myfile << -1.0f << ' ' << 0.0f << ' ' << 0.0f << ' ';
            myfile << tx2 << ' ' << tz1 << '\n';

            myfile << -offset << ' ' << y2 << ' ' << z1 << ' ';
            myfile << -1.0f << ' ' << 0.0f << ' ' << 0.0f << ' ';
            myfile << tx1 << ' ' << tz2 << '\n';

            myfile << -offset << ' ' << y1 << ' ' << z1 << ' ';
            myfile << -1.0f << ' ' << 0.0f << ' ' << 0.0f << ' ';
            myfile << tx1 << ' ' << tz1 << '\n';

            myfile << -offset << ' ' << y2 << ' ' << z2 << ' ';
            myfile << -1.0f << ' ' << 0.0f << ' ' << 0.0f << ' ';
            myfile<< tx2 << ' ' << tz2 << '\n';
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
    float p1n[3], p2n[3], p3n[3], p4n[3];

    
    for (int i = 0; i < slices; i++) {
        x1 = radius * sin(arch_alfa * i);
        x2 = radius * sin(arch_alfa * (i+1));
        z1 = radius * cos(arch_alfa * i);
        z2 = radius * cos(arch_alfa * (i+1));
     
        myfile << x1 << ' ' << 0.0f << ' ' << z1 << ' ';
        myfile << 0.0f << ' ' << -1.0f << ' ' << 0.0f << ' ';
        myfile << 0.5 + sin(arch_alfa * i) << ' ' << 0.5 + cos(arch_alfa * i) << '\n';

        myfile << 0.0f << ' ' << 0.0f << ' ' << 0.0f << ' ';
        myfile << 0.0f << ' ' << -1.0f << ' ' << 0.0f << ' ';
        myfile << (float) 0.5 << ' ' << (float) 0.5  << '\n';

        myfile << x2 << ' ' << 0.0f << ' ' << z2 << ' ';
        myfile << 0.0f << ' ' << -1.0f << ' ' << 0.0f << ' ';
        myfile << 0.5 + sin(arch_alfa * (i+1)) << ' ' << 0.5 + cos(arch_alfa * (i+1)) << '\n';
    }

    for (int i = 0; i < stacks; i++) {
        for (int j = 0; j < slices; j++) {
            h1 = height - (i * stack_size);
            h2 = height - ((i+1) * stack_size);
            r1 = h1 / ratio;
            r2 = h2 / ratio;

            x1 = r1 * sin(arch_alfa * j);
            p1n[0] = sin(arch_alfa * j);
            x2 = r1 * sin(arch_alfa * (j+1));
            p2n[0] = sin(arch_alfa * (j+1));
            x3 = r2 * sin(arch_alfa * (j+1));
            p3n[0] = sin(arch_alfa * (j+1));
            x4 = r2 * sin(arch_alfa * j);
            p4n[0] = sin(arch_alfa * j);

            y1 = (i * stack_size);
            y2 = (i+1) * stack_size;
            p1n[1]=sin(atan(radius/height));
            p2n[1]=sin(atan(radius/height));
            p3n[1]=sin(atan(radius/height));
            p4n[1]=sin(atan(radius/height));

            z1 = r1 * cos(arch_alfa * j);
            p1n[2] = cos(arch_alfa * j);
            z2 = r1 * cos(arch_alfa * (j+1));
            p2n[2] = cos(arch_alfa * (j+1));
            z3 = r2 * cos(arch_alfa * (j+1));
            p3n[2] = cos(arch_alfa * (j+1));
            z4 = r2 * cos(arch_alfa * j);
            p4n[2] = cos(arch_alfa * j);

            normalize(p1n);
            normalize(p2n);
            normalize(p3n);
            normalize(p4n);
  
            myfile << x1 << ' ' << y1 << ' ' << z1 << ' ';
            myfile << p1n[0] << ' ' << p1n[1] << ' ' << p1n[2] << ' ';
            myfile << (float) j/slices << ' ' << (float) i/stacks << '\n';

            myfile << x2 << ' ' << y1 << ' ' << z2 << ' ';
            myfile << p2n[0] << ' ' << p2n[1] << ' ' << p2n[2] << ' ';
            myfile << (float) (j+1)/slices << ' ' << (float) i/stacks << '\n';

            myfile << x4 << ' ' << y2 << ' ' << z4 << ' ';
            myfile << p4n[0] << ' ' << p4n[1] << ' ' << p4n[2] << ' ';
            myfile << (float) j/slices << ' ' << (float) (i+1)/stacks << '\n';

            if (i != stacks - 1) {
                
                myfile << x4 << ' ' << y2 << ' ' << z4 << ' ';
                myfile << p4n[0] << ' ' << p4n[1] << ' ' << p4n[2] << ' ';
                myfile << (float) j/slices << ' ' << (float) (i+1)/stacks << '\n';

                myfile << x2 << ' ' << y1 << ' ' << z2 << ' ';
                myfile << p2n[0] << ' ' << p2n[1] << ' ' << p2n[2] << ' ';
                myfile << (float) (j+1)/slices << ' ' << (float) i/stacks << '\n';

                myfile << x3 << ' ' << y2 << ' ' << z3 << ' ';
                myfile << p3n[0] << ' ' << p3n[1] << ' ' << p3n[2] << ' ';
                myfile << (float) (j+1)/slices << ' ' << (float) (i+1)/stacks << '\n';
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

    float x1, x2, x3, x4, y1, y2, y3, y4, z1, z2, z3, z4, arch_alfa = 2*M_PI / slices, arch_beta = M_PI / stacks;
    float p1n[3], p2n[3], p3n[3], p4n[3];
    

    for (int i = 0; i < slices; i++) {
        for (int j = 0; j < stacks; j++) {
            x1 = radius * cos(M_PI_2 - arch_beta * j) * sin(arch_alfa*i);
            p1n[0] = cos(M_PI_2 - arch_beta * j) * sin(arch_alfa*i);
            x2 = radius * cos(M_PI_2 - arch_beta * (j+1)) * sin(arch_alfa*i);
            p2n[0] = cos(M_PI_2 - arch_beta * (j+1)) * sin(arch_alfa*i);
            x3 = radius * cos(M_PI_2 - arch_beta * (j+1)) * sin(arch_alfa*(i+1));
            p3n[0] = cos(M_PI_2 - arch_beta * (j+1)) * sin(arch_alfa*(i+1));
            x4 = radius * cos(M_PI_2 - arch_beta * j) * sin(arch_alfa*(i+1));
            p4n[0] = cos(M_PI_2 - arch_beta * j) * sin(arch_alfa*(i+1));

            y1 = radius * sin(M_PI_2 - arch_beta*j);
            p1n[1] = sin(M_PI_2 - arch_beta*j);
            y2 = radius * sin(M_PI_2 - arch_beta * (j+1));
            p2n[1] = sin(M_PI_2 - arch_beta * (j+1));
            y3 = radius * sin(M_PI_2 - arch_beta * (j+1));
            p3n[1] = sin(M_PI_2 - arch_beta * (j+1));
            y4 = radius * sin(M_PI_2 - arch_beta*j);
            p4n[1] = sin(M_PI_2 - arch_beta*j);

            z1 = radius * cos(M_PI_2 - arch_beta * j) * cos(arch_alfa*i);
            p1n[2] = cos(M_PI_2 - arch_beta * j) * cos(arch_alfa*i);
            z2 = radius * cos(M_PI_2 - arch_beta * (j+1)) * cos(arch_alfa*i);
            p2n[2] = cos(M_PI_2 - arch_beta * (j+1)) * cos(arch_alfa*i);
            z3 = radius * cos(M_PI_2 - arch_beta * (j+1)) * cos(arch_alfa*(i+1));
            p3n[2] = cos(M_PI_2 - arch_beta * (j+1)) * cos(arch_alfa*(i+1));
            z4 = radius * cos(M_PI_2 - arch_beta * j) * cos(arch_alfa*(i+1));
            p4n[2] = cos(M_PI_2 - arch_beta * j) * cos(arch_alfa*(i+1));

            normalize(p1n);
            normalize(p2n);
            normalize(p3n);
            normalize(p4n);


            if (j != stacks-1) {
                
                myfile << x1 << ' ' << y1 << ' ' << z1 << ' ';
                myfile << p1n[0] << ' ' << p1n[1] << ' ' << p1n[2] << ' ';
                myfile << (float) i/slices << ' ' << (float) j/stacks << '\n';
                
                myfile << x2 << ' ' << y2 << ' ' << z2 << ' ';
                myfile << p2n[0] << ' ' << p2n[1] << ' ' << p2n[2] << ' ';
                myfile << (float) i/slices << ' ' << (float) (j+1)/stacks << '\n';
                
                myfile << x3 << ' ' << y3 << ' ' << z3 << ' ';            
                myfile << p3n[0] << ' ' << p3n[1] << ' ' << p3n[2] << ' ';
                myfile << (float) (i+1)/slices << ' ' << (float) (j+1)/stacks << '\n';

            }
        
            if (j != 0) {
                
                myfile << x1 << ' ' << y1 << ' ' << z1 << ' ';  
                myfile << p1n[0] << ' ' << p1n[1] << ' ' << p1n[2] << ' ';
                myfile << (float) i/slices << ' ' << (float) j/stacks << '\n';
                
                myfile << x3 << ' ' << y3 << ' ' << z3 << ' ';
                myfile << p3n[0] << ' ' << p3n[1] << ' ' << p3n[2] << ' ';
                myfile << (float) (i+1)/slices << ' ' << (float) (j+1)/stacks << '\n';
                
                myfile << x4 << ' ' << y4 << ' ' << z4 << ' ';
                myfile << p4n[0] << ' ' << p4n[1] << ' ' << p4n[2] << ' ';
                myfile << (float) (i+1)/slices << ' ' << (float) j/stacks << '\n';

            }


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
    float p1n[3], p2n[3], p3n[3], p4n[3];

    max_radius = (max_radius + min_radius) / 2;
    min_radius = max_radius - min_radius;

    for (int i = 0; i < stacks; i++) {
        for (int j = 0; j < slices; j++) {

            x1 = (max_radius + min_radius * cos(arch_alpha * i)) * cos(arch_beta * j);
            p1n[0]=(min_radius * cos(arch_alpha * i)) * cos(arch_beta * j);
            x2 = (max_radius + min_radius * cos(arch_alpha * (i+1))) * cos(arch_beta * j);
            p2n[0]=(min_radius * cos(arch_alpha * (i+1))) * cos(arch_beta * j);
            x3 = (max_radius + min_radius * cos(arch_alpha * (i+1))) * cos(arch_beta * (j+1));
            p3n[0]=(min_radius * cos(arch_alpha * (i+1))) * cos(arch_beta * (j+1));
            x4 = (max_radius + min_radius * cos(arch_alpha * i)) * cos(arch_beta * (j+1));
            p4n[0]=(min_radius * cos(arch_alpha * i)) * cos(arch_beta * (j+1));

            y1 = min_radius * sin(arch_alpha * i);
            p1n[1]=min_radius * sin(arch_alpha * i);
            y2 = min_radius * sin(arch_alpha * (i+1));
            p2n[1]=min_radius * sin(arch_alpha * (i+1));
            y3 = min_radius * sin(arch_alpha * (i+1));
            p3n[1]=min_radius * sin(arch_alpha * (i+1));
            y4 = min_radius * sin(arch_alpha * i);
            p4n[1]=min_radius * sin(arch_alpha * i);

            z1 = (max_radius + min_radius * cos(arch_alpha * i)) * sin(arch_beta * j);
            p1n[2]=(min_radius * cos(arch_alpha * i)) * sin(arch_beta * j);
            z2 = (max_radius + min_radius * cos(arch_alpha * (i+1))) * sin(arch_beta * j);
            p2n[2]=(min_radius * cos(arch_alpha * (i+1))) * sin(arch_beta * j);
            z3 = (max_radius + min_radius * cos(arch_alpha * (i+1))) * sin(arch_beta * (j+1));
            p3n[2]=(min_radius * cos(arch_alpha * (i+1))) * sin(arch_beta * (j+1));
            z4 = (max_radius + min_radius * cos(arch_alpha * i)) * sin(arch_beta * (j+1));
            p4n[2]=(min_radius * cos(arch_alpha * i)) * sin(arch_beta * (j+1));

            normalize(p1n);
            normalize(p2n);
            normalize(p3n);
            normalize(p4n);

            myfile << x1 << ' ' << y1 << ' ' << z1 << ' ';
            myfile << p1n[0] << ' ' << p1n[1] << ' ' << p1n[2] << ' ';
            myfile << (float)  i/stacks << ' ' << (float) j/slices << '\n';

            myfile << x2 << ' ' << y2 << ' ' << z2 << ' ';
            myfile << p2n[0] << ' ' << p2n[1] << ' ' << p2n[2] << ' ';
            myfile << (float)  (i+1)/stacks << ' ' << (float) j/slices << '\n';

            myfile << x4 << ' ' << y4 << ' ' << z4 << ' ';
            myfile << p4n[0] << ' ' << p4n[1] << ' ' << p4n[2] << ' ';
            myfile << (float) i/stacks << ' ' << (float) (j+1)/slices  << '\n';

            myfile << x2 << ' ' << y2 << ' ' << z2 << ' ';
            myfile << p2n[0] << ' ' << p2n[1] << ' ' << p2n[2] << ' ';
            myfile << (float) (i+1)/stacks << ' ' << (float) j/slices  << '\n';

            myfile << x3 << ' ' << y3 << ' ' << z3 << ' ';
            myfile << p3n[0] << ' ' << p3n[1] << ' ' << p3n[2] << ' ';
            myfile << (float) (i+1)/stacks << ' ' << (float) (j+1)/slices << '\n';

            myfile << x4 << ' ' << y4 << ' ' << z4 << ' ';
            myfile << p4n[0] << ' ' << p4n[1] << ' ' << p4n[2] << ' ';
            myfile << (float) i/stacks << ' ' << (float) (j+1)/slices  << '\n';

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


void crossProd(float *a, float *b, float *res) {

    res[0] = a[1]*b[2] - a[2]*b[1];
    res[1] = a[2]*b[0] - a[0]*b[2];
    res[2] = a[0]*b[1] - a[1]*b[0];
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

float derivU(float U, float V, float m[4][4]){

    float aux[4];
    float v[4];
    float r;

    v[0] = powf(V,3);
    v[1] = powf(V,2);
    v[2] = V;
    v[3] = 1;

    multMatrixVector(m,v,aux);

    r = 3*powf(U,2)*aux[0] + 2*U*aux[1] + aux[2];

    return r;
}

float derivV(float U, float V, float m[4][4]){

    float aux[4];
    float v[4];
    float r;

    v[0] = 3*powf(V,2);
    v[1] = 2*V;
    v[2] = 1;
    v[3] = 0;

    multMatrixVector(m,v,aux);

    r = powf(U,3)*aux[0] + powf(U,2)*aux[1] + U*aux[2] + aux[3];

    return r;
}


std::string surface(float mx[4][4], float my[4][4], float mz[4][4], int tesselation){

    std::stringstream buffer;

    float x1, x2, x3, x4, y1, y2, y3, y4, z1, z2, z3, z4;
    float p1u[3], p2u[3], p3u[3], p4u[3], p1v[3], p2v[3], p3v[3], p4v[3], p1n[3], p2n[3], p3n[3], p4n[3]; 
    float tesselation_level = 1.0/tesselation;

    for(float i=0; i<1; i+=tesselation_level){
        for(float j=0; j<1; j+=tesselation_level){

            x1 = B(i,j,mx);
            p1u[0]=derivU(i,j,mx);
            p1v[0]=derivV(i,j,mx);

            x2 = B(i+tesselation_level,j,mx);
            p2u[0]=derivU(i+tesselation_level,j,mx);
            p2v[0]=derivV(i+tesselation_level,j,mx);

            x3 = B(i+tesselation_level,j+tesselation_level,mx);
            p3u[0]=derivU(i+tesselation_level,j+tesselation_level,mx);
            p3v[0]=derivV(i+tesselation_level,j+tesselation_level,mx);

            x4 = B(i,j+tesselation_level,mx);
            p4u[0]=derivU(i,j+tesselation_level,mx);
            p4v[0]=derivV(i,j+tesselation_level,mx);


            y1 = B(i,j,my);
            p1u[1]=derivU(i,j,my);   
            p1v[1]=derivV(i,j,my);

            y2 = B(i+tesselation_level,j,my);
            p2u[1]=derivU(i+tesselation_level,j,my);
            p2v[1]=derivV(i+tesselation_level,j,my);

            y3 = B(i+tesselation_level,j+tesselation_level,my);
            p3u[1]=derivU(i+tesselation_level,j+tesselation_level,my);
            p3v[1]=derivV(i+tesselation_level,j+tesselation_level,my);

            y4 = B(i,j+tesselation_level,my);
            p4u[1]=derivU(i,j+tesselation_level,my);
            p4v[1]=derivV(i,j+tesselation_level,my);

            z1 = B(i,j,mz);
            p1u[2]=derivU(i,j,mz);
            p1v[2]=derivV(i,j,mz);

            z2 = B(i+tesselation_level,j,mz);
            p2u[2]=derivU(i+tesselation_level,j,mz);
            p2v[2]=derivV(i+tesselation_level,j,mz);

            z3 = B(i+tesselation_level,j+tesselation_level,mz);
            p3u[2]=derivU(i+tesselation_level,j+tesselation_level,mz);
            p3v[2]=derivV(i+tesselation_level,j+tesselation_level,mz);

            z4 = B(i,j+tesselation_level,mz);
            p4u[2]=derivU(i,j+tesselation_level,mz);
            p4v[2]=derivV(i,j+tesselation_level,mz);

            crossProd(p1u,p1v,p1n);
            crossProd(p2u,p2v,p2n);
            crossProd(p3u,p3v,p3n);
            crossProd(p4u,p4v,p4n);

            normalize(p1n);
            normalize(p2n);
            normalize(p3n);
            normalize(p4n);

   
            buffer << x1 << ' ' << y1 << ' ' << z1 << ' ';
            buffer << p1n[0] << ' ' << p1n[1] << ' ' << p1n[2] << ' ';
            buffer << i << ' ' << j << '\n';  // Corrected order for texture coordinates

            buffer << x2 << ' ' << y2 << ' ' << z2 << ' ';
            buffer << p2n[0] << ' ' << p2n[1] << ' ' << p2n[2] << ' ';
            buffer << (i + tesselation_level) << ' ' << j << '\n';  // Corrected order for texture coordinates

            buffer << x4 << ' ' << y4 << ' ' << z4 << ' ';
            buffer << p4n[0] << ' ' << p4n[1] << ' ' << p4n[2] << ' ';
            buffer << i << ' ' << (j + tesselation_level) << '\n';  // Corrected order for texture coordinates

            buffer << x2 << ' ' << y2 << ' ' << z2 << ' ';
            buffer << p2n[0] << ' ' << p2n[1] << ' ' << p2n[2] << ' ';
            buffer << (i + tesselation_level) << ' ' << j << '\n';  // Corrected order for texture coordinates

            buffer << x3 << ' ' << y3 << ' ' << z3 << ' ';
            buffer << p3n[0] << ' ' << p3n[1] << ' ' << p3n[2] << ' ';
            buffer << (i + tesselation_level) << ' ' << (j + tesselation_level) << '\n';  // Corrected order for texture coordinates

            buffer << x4 << ' ' << y4 << ' ' << z4 << ' ';
            buffer << p4n[0] << ' ' << p4n[1] << ' ' << p4n[2] << ' ';
            buffer << i << ' ' << (j + tesselation_level) << '\n'; 
    /*

            buffer << x1 << ' ' << y1 << ' ' << z1 << ' ';
            buffer << p1n[0] << ' ' << p1n[1] << ' ' << p1n[2] << ' ';
            buffer << j << ' ' << i << '\n';

            buffer << x2 << ' ' << y2 << ' ' << z2 << ' ';
            buffer << p2n[0] << ' ' << p2n[1] << ' ' << p2n[2] << ' ';
            buffer << j << ' ' << i+tesselation_level << '\n';

            buffer << x3 << ' ' << y3 << ' ' << z3 << ' ';
            buffer << p3n[0] << ' ' << p3n[1] << ' ' << p3n[2] << ' ';
            buffer << j+tesselation_level << ' ' << i+tesselation_level << '\n';
            
            buffer << x3 << ' ' << y3 << ' ' << z3 << ' ';
            buffer << p3n[0] << ' ' << p3n[1] << ' ' << p3n[2] << ' ';
            buffer << j+tesselation_level << ' ' << i+tesselation_level << '\n';
            
            buffer << x4 << ' ' << y4 << ' ' << z4 << ' ';
            buffer << p4n[0] << ' ' << p4n[1] << ' ' << p4n[2] << ' ';
            buffer << j+tesselation_level << ' ' << i << '\n';
            
            buffer << x1 << ' ' << y1 << ' ' << z1 << ' ';
            buffer << p1n[0] << ' ' << p1n[1] << ' ' << p1n[2] << ' ';
            buffer << j << ' ' << i << '\n';
    */
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











