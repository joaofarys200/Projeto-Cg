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
std::vector<std::pair<std::string,int>> ficheiros;
std::vector<std::pair<std::string,int>> info;
std::vector<std::pair<std::vector<std::string>,int>> transf;
std::vector<std::pair<std::vector<std::string>,int>> final;
std::vector<int> pais;
int contador = 0;


//função que recebe um elemento xml, e percorre os seus atributos, recolhendo informaçôes referentes à câmara e à janela, 
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

    }

    dist=sqrt(camx*camx + camy*camy + camz*camz);
    beta = asin(camy / dist);
    alpha = asin(camx / (dist * cos(beta)));
}


//percorre todo o ficheiro elemento do ficheiro xml, chamando recursivamente a funçao, para cada elemento, chama a função get_attributes
void traverse_elements(tinyxml2::XMLElement* element) {
    get_attributes(element);

    for (tinyxml2::XMLElement* child = element->FirstChildElement(); child; child = child->NextSiblingElement()) {
        traverse_elements(child);
    }
}


//Funçaõ recursiva, percorre o ficheiro xml, recolhendo informação sobre o elemento, e o pai do elemento
void get_transformacoes(tinyxml2::XMLElement* element, std::string pai = "Null", int painum=-1) {

    //recebe como paremetro o identificador do seu pai, que chamou a função recursivamente, e guarda-o no vetor pais
    std::string elementName = element->Name(); 
    int num=contador;
    pais.push_back(painum);

    //caso seja uma transformação, percorre os atributos, e guarda os valores de angle,x,y,z em tranfs. guarda o nome do elemento no vetor info
    if(elementName=="translate" or elementName=="rotate" or elementName=="scale"){ 
        info.push_back(std::make_pair(elementName, contador));
        std::vector<std::string> valores;
        for (const tinyxml2::XMLAttribute* attr = element->FirstAttribute(); attr; attr = attr->Next()){ 
            valores.push_back(std::string(attr->Value()));
        }
        transf.push_back(std::make_pair(valores, contador));
    }

    //caso seja um ficheiro, guarda o seu path para o vetor ficheiros, e para o vetor info
    else if(elementName=="model"){ 
        const tinyxml2::XMLAttribute* attr = element->FirstAttribute();
        //"../tests/"+std::string(attr->Value())
        info.push_back(std::make_pair("tests/"+std::string(attr->Value()), contador));
        ficheiros.push_back(std::make_pair("tests/"+std::string(attr->Value()), contador));
    }


    //caso contrario, apenas guarda o nome do elemento para o vetor info
    else{
        info.push_back(std::make_pair(std::string(element->Name()), contador));
    }


    contador+=1;
 
    //percorre todos os filhos do elemento e chama recursivamente a função para eles, dando o seu identificador como atributo
    for (tinyxml2::XMLElement* child = element->FirstChildElement(); child != nullptr; child = child->NextSiblingElement()) {
        
        get_transformacoes(child, elementName,num); 
    }
}



void organiza_vetores(){
    
    for(int i=0; i<ficheiros.size(); i++){    //percorremos todos os ficheiros
        int pai=pais[ficheiros[i].second];    
        while(pai!=-1){                      //para cada um, percorremos todos os seus pais

            for(size_t j=pais[pai]; j<info.size()-1; j++){   //percorremos todos os elementos de novo

//se o do pai de um elemento coincidir com um pai do ficheiro temos que o analisar, pois se houver alguma transformação, temos que a ter em conta

                if(pais[j]==pais[pai] and info[j].first=="transform"){   
        
                    for(size_t k=info.size()-1; k>=j+1; k--){                      

                        if(pais[k]==j){                                             //se encontrarmos uma rotação, translaçã́o. escala, esta terá o pai transform
                        
                            for(size_t l=0; l<transf.size();l++){                    //percorremos o vetor das transformações   
                                std::vector<std::string> aux;      

                                if(transf[l].second==info[k].second){                //se encontramos a transformação que procuravamos, obtemos os seus valores 
                                    aux.push_back(info[k].first);

                                    for(size_t m=0; m<transf[l].first.size(); m++){
                                        aux.push_back(transf[l].first[m]);
                                    }

                                    final.push_back(std::make_pair(aux,i));          //guardamos a transformação, e o identificador do ficheiro no vetor final
                                
                                }
                            }
                            
                        }   
                        
                    }
                }

            }
            pai=pais[pai];     
        }
    
    }


}


//percorre o vetor ficheiros, para cada elemento, percorre o ficheiro e guarda os valores
void get_numbers(){
    for (auto& elem : ficheiros) { 
        std::ifstream f(elem.first);

        std::vector<float> numbersArray; 

        std::string linha;

        //percorre todas as linhas do ficheiro
        while (std::getline(f, linha)) {
            std::string xstr="";
            std::string ystr="";
            std::string zstr="";
            float x;
            float y;
            float z;
            int contador=0;          //representa o nº de espaços encontrados em cada linha
            for(char a : linha){

                if(a!=' ' && a!='\n'){ //se o nº de espaços for 0, estamos a copiar o valor de x
                    if(contador==0){
                        xstr+=a;
                    }

                    else if(contador==1){ //se o nº de espaços for 0, estamos a copiar o valor de y
                        ystr+=a;
                    }

                    else if(contador==2){ //se o nº de espaços for 0, estamos a copiar o valor de z
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
            numbersArray.push_back(y);    //guardamos os valores no vetor
            numbersArray.push_back(z);
        }
        numbersArrays.push_back(numbersArray); //guardamos o vetor no vetor de vetores
    }
}


void draw() {

    for (size_t i = 0; i < numbersArrays.size(); i++) {    //percorremos todos todos os vetores de pontos no vetor (cada vetor representa um ficheiro .3d)

        glPushMatrix();                                   //empilhamos a matriz identidade na pilha

        for(int k=final.size()-1;k>=0;k--){               //percorremos todas as transformações no vetor das transformações
            
            if(i==final[k].second){                   //se o identificador do ficheiro for igual ao numero do vetor (que representa um ficheiro .3d) procedemos

                //verificamos qual a transformação geométrica em questao e obtemos os valores, efetuando a transformação

                if(final[k].first[0]=="translate"){      
                    glTranslatef(std::stod(final[k].first[1]),std::stod(final[k].first[2]),std::stod(final[k].first[3]));

                }
                else if(final[k].first[0]=="rotate"){
                    glRotatef(std::stod(final[k].first[1]),std::stod(final[k].first[2]),std::stod(final[k].first[3]),std::stod(final[k].first[4]));
                    
                }
                else if(final[k].first[0]=="scale"){
                    glScalef(std::stod(final[k].first[1]),std::stod(final[k].first[2]),std::stod(final[k].first[3]));
                    
                }

                
            }
        } 

        //com todas as transformações geométricas feitas, desenhamos agora os triangulos, são lidos 3 números de cada vez (coordenadas do vertice)

        glBegin(GL_TRIANGLES); 

        for (size_t j = 0; j <= numbersArrays[i].size()-3; j+=3) { 
                
            glVertex3f(numbersArrays[i][j], numbersArrays[i][j+1], numbersArrays[i][j+2]);
        }
   
        glEnd(); 
        glPopMatrix(); //retomamos a matriz identidade anteriormente empilhada na stack
        
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

    glColor3f(1.0f, 1.0f, 1.0f); 
    draw();
    
    glutSwapBuffers();
}


int main(int argc, char **argv) {

    if(argc!=2){
        std::cout << "numero incorreto de argumentos\n";
        return 1;
    }


    tinyxml2::XMLDocument doc;
    std::string xmlFilePath = "tests/" + std::string(argv[1]);
    doc.LoadFile(xmlFilePath.c_str());


    tinyxml2::XMLElement* root = doc.RootElement();
    if (root) {
        traverse_elements(root);
    }


    root = doc.RootElement();
    if (!root) {
        std::cout << "Elemento raiz ausente no arquivo XML.\n";
        return 1;
    }


    root=root->FirstChildElement();               // a função que extrai informação sobre transformações 
    while(std::string(root->Name())!="group"){    // só é chamada quando é encontrado o 1º elemento group
        root=root->NextSiblingElement();
    }

    get_transformacoes(root);

    organiza_vetores();

    get_numbers();
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(width, height);
    glutCreateWindow("lcc_gr15_fase2");

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