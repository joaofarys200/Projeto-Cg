#define _USE_MATH_DEFINES
#include <stdlib.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "tinyxml2.h"

double camx;
double camy;
double camz;

int width;
int height;

double lookx;
double looky;
double lookz;

double upx;
double upy;
double upz;

double fov;
double near;
double far;

double dist;

double alpha; // horizontal
double beta;  // vertical


std::vector<std::vector<float>> numbersArrays; 

std::vector<std::string> ficheiros;


void get_attributes(tinyxml2::XMLElement* element) {
    for (const tinyxml2::XMLAttribute* attr = element->FirstAttribute(); attr; attr = attr->Next()) {

        if(std::string(element->Name())=="window"){

            if(std::string(attr->Name())=="width"){
                width=std::stoi(attr->Value());
            }

            else if(std::string(attr->Name())=="height"){
                height=std::stoi(attr->Value());
            }

        }


        else if(std::string(element->Name())=="lookAt"){

            if(std::string(attr->Name())=="x"){
                lookx=std::stod(attr->Value());
            }

            else if(std::string(attr->Name())=="y"){
                looky=std::stod(attr->Value());
            }

            else if(std::string(attr->Name())=="z"){
                lookz=std::stod(attr->Value());
            }
        }


        else if(std::string(element->Name())=="up"){

            if(std::string(attr->Name())=="x"){
                upx=std::stod(attr->Value());
            }

            else if(std::string(attr->Name())=="y"){
                upy=std::stod(attr->Value());
            }

            else if(std::string(attr->Name())=="z"){
                upz=std::stod(attr->Value());
            }
        }



        else if(std::string(element->Name())=="projection"){

            if(std::string(attr->Name())=="fov"){
                fov=std::stod(attr->Value());
            }

            else if(std::string(attr->Name())=="near"){
                near=std::stod(attr->Value());
            }

            else if(std::string(attr->Name())=="far"){
                far=std::stod(attr->Value());
            }

        }



        else if(std::string(element->Name())=="position"){

            if(std::string(attr->Name())=="x"){
                camx=std::stod(attr->Value());
            }

            else if(std::string(attr->Name())=="y"){
                camy=std::stod(attr->Value());
            }

            else if(std::string(attr->Name())=="z"){
                camz=std::stod(attr->Value());
            }
        }


        else if (std::string(element->Name())=="model" && std::string(attr->Name())=="file"){
            //ficheiros.push_back("../tests/"+std::string(attr->Value()));
            ficheiros.push_back("tests/"+std::string(attr->Value()));
        }
    }

    dist=sqrt(camx*camx + camy*camy + camz*camz);
    beta = asin(camy / dist);
    alpha = asin(camx / (dist * cos(beta)));
}


void traverse_elements(tinyxml2::XMLElement* element) {
    get_attributes(element);

    for (tinyxml2::XMLElement* child = element->FirstChildElement(); child; child = child->NextSiblingElement()) {
        traverse_elements(child);
    }
}


void get_numbers(){
    for (auto& elem : ficheiros) { 
        std::ifstream f(elem);

        std::vector<float> numbersArray;

        std::string linha;
        while (std::getline(f, linha)) {
            std::string xstr="";
            std::string ystr="";
            std::string zstr="";
            float x;
            float y;
            float z;
            int contador=0;
            for(char a : linha){

                if(a!=' ' && a!='\n'){
                    if(contador==0){
                        xstr+=a;
                    }

                    else if(contador==1){
                        ystr+=a;
                    }

                    else if(contador==2){
                        zstr+=a;
                    }
                }

                else if(a==' '){
                    contador+=1;
                }
            }

            x = std::stof(xstr);
            y = std::stof(ystr);
            z = std::stof(zstr);

            numbersArray.push_back(x);
            numbersArray.push_back(y);
            numbersArray.push_back(z);
        }
        numbersArrays.push_back(numbersArray);
    }
}



void changeSize(int w, int h) {
    // Prevent a divide by zero, when window is too short
    // (you cant make a window with zero width).
    if(h == 0)
        h = 1;

    // compute window's aspect ratio 
    float ratio = w * 1.0 / h;

    // Set the projection matrix as current
    glMatrixMode(GL_PROJECTION);
    // Load Identity Matrix
    glLoadIdentity();
    
    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Set perspective
    gluPerspective(fov ,ratio, near ,far);

    // return to the model view matrix mode
    glMatrixMode(GL_MODELVIEW);
}



void keyboardSpecial(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_LEFT:
    alpha -= 0.1f;
    break;
    case GLUT_KEY_RIGHT:
    alpha += 0.1f;
    break;
    case GLUT_KEY_UP:
    beta += 0.1f;
    break;
    case GLUT_KEY_DOWN:
    beta -= 0.1f;
    break;
    }
    //alpha = std::clamp(alpha, -1.5, 1.5);
    //beta = std::clamp(beta, -1.5, 1.5);
    glutPostRedisplay();
}


void draw() {
    
    for (size_t i = 0; i < numbersArrays.size(); i++) { 
        glBegin(GL_TRIANGLES); 

        for (size_t j = 0; j <= numbersArrays[i].size()-3; j+=3) { 
                
            glVertex3f(numbersArrays[i][j], numbersArrays[i][j+1], numbersArrays[i][j+2]);
        }
        glEnd(); 

    }
    
}



void renderScene(void) {

    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set camera
    glLoadIdentity();

    camz = dist * cos(beta) * cos(alpha);
    camx = dist * cos(beta) * sin(alpha);
    camy = dist * sin(beta);

    gluLookAt(camx, camy, camz, lookx, looky, lookz, upx, upy, upz);

    glColor3f(1.0f, 1.0f, 1.0f);
    draw();

    glBegin(GL_LINES);
    glColor3f(1.0f, 0.0f, 0.0f); // X-axis (red)
    glVertex3f(-100.0f, 0.0f, 0.0f);
    glVertex3f(100.0f, 0.0f, 0.0f);

    glColor3f(0.0f, 1.0f, 0.0f); // Y-axis (green)
    glVertex3f(0.0f, -100.0f, 0.0f);
    glVertex3f(0.0f, 100.0f, 0.0f);

    glColor3f(0.0f, 0.0f, 1.0f); // Z-axis (blue)
    glVertex3f(0.0f, 0.0f, -100.0f);
    glVertex3f(0.0f, 0.0f, 100.0f);
    glEnd();
    
    glutSwapBuffers();
}


int main(int argc, char **argv) {

    if(argc!=2){
        std::cout << "numero incorreto de argumentos\n";
        return 1;
    }


    tinyxml2::XMLDocument doc;
    //std::string xmlFilePath = "../tests/" + std::string(argv[1]);
    std::string xmlFilePath = "tests/" + std::string(argv[1]);
    doc.LoadFile(xmlFilePath.c_str());

    tinyxml2::XMLElement* root = doc.RootElement();
    if (root) {
        traverse_elements(root);
    }

    get_numbers();
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(width, height);
    glutCreateWindow("lcc_gr15_fase1");

    // Required callback registry 
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutSpecialFunc(keyboardSpecial);

    // OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

    glutPostRedisplay();

    glutMainLoop();
    return 0;
}
