#define _USE_MATH_DEFINES
#include <stdlib.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include<tuple>
#include "tinyxml2.h"

#define TESSELATION 100.0

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
double near_;
double far_;

double dist;

double alpha; // horizontal
double beta;  // vertical

float cameraX=0.0f,cameraY=0.0f,cameraZ=5.0f; // Camera position
float cameraYaw=0.0f,cameraPitch=0.0f;

bool CameraType=false;

// change!!!!!
double distSpeed=0.1;
int scene = 0;
bool objP=false;
std::tuple<float,float,float> objEx;

int eixos=1;

std::vector<std::tuple<float, float, float>> objPos;
std::vector<std::vector<float>> numbersArrays;        
std::vector<std::pair<std::string,int>> ficheiros;
std::vector<std::pair<std::string,int>> info;
std::vector<std::pair<std::vector<std::string>,int>> transf;
std::vector<std::pair<std::vector<std::string>,int>> final; 
std::vector<int> pais;
int contador = 0;
std::vector<GLuint> vbo(numbersArrays.size());

//função que recebe um elemento xml, e percorre os seus atributos, recolhendo informaçôes referentes à câmara e à janela, 
void get_attributes(tinyxml2::XMLElement* element) { 
    for (const tinyxml2::XMLAttribute* attr = element->FirstAttribute(); attr; attr = attr->Next()) {

        if(std::string(element->Name())=="eixos"){
            if(std::string(attr->Value())=="yes"){
                eixos=1;
            }
            else if(std::string(attr->Value())=="no"){
                eixos=0;
            }

        }

        else if(std::string(element->Name())=="window"){

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
                near_=std::stod(attr->Value());
            }

            else if(std::string(attr->Name())=="far"){
                far_=std::stod(attr->Value());
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

    dist=sqrt(camx + camy + camz * camz);
    beta=asin(camy / dist);
    alpha=atan2(camx,camz);
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
        const tinyxml2::XMLAttribute* attr = element->FirstAttribute();

        if(elementName=="translate" && std::string(attr->Name())=="time"){

            info.push_back(std::make_pair("translatet", contador));
            std::vector<std::string> valores;

            for (const tinyxml2::XMLAttribute* attr = element->FirstAttribute(); attr; attr = attr->Next()){
                valores.push_back(std::string(attr->Value()));
            }
            for (tinyxml2::XMLElement* child = element->FirstChildElement(); child; child = child->NextSiblingElement()) {
                for (const tinyxml2::XMLAttribute* attr2 = child->FirstAttribute(); attr2; attr2 = attr2->Next()){
                    valores.push_back(std::string(attr2->Value()));
                }
            }
            valores.push_back("0");
            transf.push_back(std::make_pair(valores, contador));

        }


        else if(elementName=="rotate" && std::string(attr->Name())=="time"){
            info.push_back(std::make_pair("rotatet", contador));
            std::vector<std::string> valores;
            for (const tinyxml2::XMLAttribute* attr = element->FirstAttribute(); attr; attr = attr->Next()){
                valores.push_back(std::string(attr->Value()));
            }
            transf.push_back(std::make_pair(valores, contador));


        }
        else{
            info.push_back(std::make_pair(elementName, contador));
            std::vector<std::string> valores;
            for (const tinyxml2::XMLAttribute* attr = element->FirstAttribute(); attr; attr = attr->Next()){
                valores.push_back(std::string(attr->Value()));
            }
            transf.push_back(std::make_pair(valores, contador));

        }
        

    }

    //caso seja um ficheiro, guarda o seu path para o vetor ficheiros, e para o vetor info
    else if(elementName=="model"){ 
        const tinyxml2::XMLAttribute* attr = element->FirstAttribute();
        //"../tests/"+std::string(attr->Value())
        info.push_back(std::make_pair(std::string(attr->Value()), contador));
        ficheiros.push_back(std::make_pair(std::string(attr->Value()), contador));
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

void buildRotMatrix(float *x, float *y, float *z, float *m) {

    m[0] = x[0]; m[1] = x[1]; m[2] = x[2]; m[3] = 0;
    m[4] = y[0]; m[5] = y[1]; m[6] = y[2]; m[7] = 0;
    m[8] = z[0]; m[9] = z[1]; m[10] = z[2]; m[11] = 0;
    m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;
}

void cross(float *a, float *b, float *res) {

    res[0] = a[1]*b[2] - a[2]*b[1];
    res[1] = a[2]*b[0] - a[0]*b[2];
    res[2] = a[0]*b[1] - a[1]*b[0];
}

void normalize(float *a) {

    float l = sqrt(a[0]*a[0] + a[1] * a[1] + a[2] * a[2]);
    a[0] = a[0]/l;
    a[1] = a[1]/l;
    a[2] = a[2]/l;
}

float length(float *v) {

    float res = sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
    return res;

}

void multMatrixVector(float m[4][4], float *v, float *res) {

    for (int j = 0; j < 4; ++j) {
        res[j] = 0;
        for (int k = 0; k < 4; ++k) {
            res[j] += v[k] * m[j][k];
        }
    }

}

void getCatmullRomPoint(float t, float *p0, float *p1, float *p2, float *p3, float *pos, float *deriv) {

    // catmull-rom matrix
    float m[4][4] = {   {-0.5f,  1.5f, -1.5f,  0.5f},
                        { 1.0f, -2.5f,  2.0f, -0.5f},
                        {-0.5f,  0.0f,  0.5f,  0.0f},
                        { 0.0f,  1.0f,  0.0f,  0.0f}};


    for(int i = 0; i < 3; i++) {     // i = x, y, z
        float p[4] = {p0[i], p1[i], p2[i], p3[i]};
        float a[4];
        // Compute A = M * P
        multMatrixVector(m, p, a);
        
        pos[i] = powf(t,3.0) * a[0] + powf(t,2.0) * a[1] + t * a[2] + a[3];
        // Compute pos = T * A
        
        // compute deriv = T' * A
        deriv[i] = 3*powf(t,2.0) * a[0] + 2 * t * a[1] + a[2];

        // ...
    }
}

// given  global t, returns the point in the curve
void getGlobalCatmullRomPoint(float gt, float *pos, float *deriv,std::vector<std::vector<float>> p) {

    int point_count=p.size();
    float t = gt * point_count; // this is the real global t
    int index = floor(t);  // which segment
    t = t - index; // where within  the segment

    // indices store the points
    int indices[4]; 
    indices[0] = (index + point_count-1)%point_count;   
    indices[1] = (indices[0]+1)%point_count;
    indices[2] = (indices[1]+1)%point_count; 
    indices[3] = (indices[2]+1)%point_count;

    float *p0 = p[indices[0]].data();
    float *p1 = p[indices[1]].data();
    float *p2 = p[indices[2]].data();
    float *p3 = p[indices[3]].data();
    
    // Call getCatmullRomPoint with pointers
    getCatmullRomPoint(t, p0, p1, p2, p3, pos, deriv);

}

void renderCatmullRomCurve(std::vector<std::vector<float>> p) {

    float pos[3];
    float deriv[3];

// draw curve using line segments with GL_LINE_LOOP
    glBegin(GL_LINE_LOOP);
    float gt = 0;
    while (gt < 1) {
        getGlobalCatmullRomPoint(gt, pos, deriv,p);
        glVertex3f(pos[0],pos[1],pos[2]);
        gt += 1.0/TESSELATION;
    }
    glEnd();
}

float prev_y[3] = {0,-1,0};

void draw() {

    for (size_t i = 0; i < vbo.size(); i++) {    //percorremos todos todos os vetores de pontos no vetor (cada vetor representa um ficheiro .3d)
        
        glBindBuffer(GL_ARRAY_BUFFER, vbo[i]);
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, 0);

        glPushMatrix();                                   //empilhamos a matriz identidade na pilha
        if ( !objP ) {
            float modelview[ 16 ];
            glGetFloatv(GL_MODELVIEW_MATRIX,modelview);
            // Extract the translation components
            float tx=modelview[ 12 ];
            float ty=modelview[ 13 ];
            float tz=modelview[ 14 ];
            objEx=std::make_tuple( tx, ty, tz);
        }
        for(int k=final.size()-1;k>=0;k--){               //percorremos todas as transformações no vetor das transformações

            if(i==final[k].second){                   //se o identificador do ficheiro for igual ao numero do vetor (que representa um ficheiro .3d) procedemos

                //verificamos qual a transformação geométrica em questao e obtemos os valores, efetuando a transformação
                if(final[k].first[0]=="translate"){     
                    float tempx=std::stof(final[ k ].first[ 1 ]);
                    float tempy=std::stof(final[ k ].first[ 2 ]);
                    float tempz=std::stof(final[ k ].first[ 3 ]);
                    glTranslatef(tempx,tempy,tempz);
                    
                }
                else if(final[k].first[0]=="rotate"){
                    glRotatef(std::stod(final[k].first[1]),std::stod(final[k].first[2]),std::stod(final[k].first[3]),std::stod(final[k].first[4]));
                    
                }
                else if(final[k].first[0]=="scale"){
                    glScalef(std::stod(final[k].first[1]),std::stod(final[k].first[2]),std::stod(final[k].first[3]));
                    
                }
                
                else if(final[k].first[0]=="rotatet"){
                    float tempo=std::stod(final[k].first[1])*1000;
                    float angulo=glutGet(GLUT_ELAPSED_TIME)*360/tempo;
                    glRotatef(angulo,std::stod(final[k].first[2]),std::stod(final[k].first[3]),std::stod(final[k].first[4]));
                }

                else if(final[k].first[0]=="translatet"){

                    float time=std::stod(final[k].first[1]);
                    std::vector<std::vector<float>> pontos;
                    for(int a = 3; a<final[k].first.size()-3; a+=3){
                        std::vector<float> ponto;
                        ponto.push_back(std::stod(final[k].first[a]));
                        ponto.push_back(std::stod(final[k].first[a+1]));
                        ponto.push_back(std::stod(final[k].first[a+2]));
                        pontos.push_back(ponto);
                    }

                    renderCatmullRomCurve(pontos);
                    
                }

              
            }
        
        } 

        if ( !objP ) {
            float modelview[ 16 ];
            glGetFloatv(GL_MODELVIEW_MATRIX,modelview);
            // Extract the translation components
            float tx=modelview[ 12 ];
            float ty=modelview[ 13 ];
            float tz=modelview[ 14 ];
            objPos.push_back(std::make_tuple(tx-std::get<0>(objEx),ty - std::get<1>(objEx),tz - std::get<2>(objEx)));
            
        }

        //com todas as transformações geométricas feitas, desenhamos agora os triangulos, são lidos 3 números de cada vez (coordenadas do vertice)
        glDrawArrays(GL_TRIANGLES, 0, numbersArrays[i].size() / 3);

        // Disable vertex array
        glDisableClientState(GL_VERTEX_ARRAY);

        glPopMatrix();
        
    }
    objP=true;
    glutSwapBuffers();
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
    gluPerspective(fov ,ratio, near_ ,far_);

    // return to the model view matrix mode
    glMatrixMode(GL_MODELVIEW);
}

void keyboardSpecial(int key, int x, int y) {
    if ( CameraType ) {
        float angleSpeed=2.0f;
        switch ( key ) {
        case GLUT_KEY_UP: cameraPitch-=angleSpeed; break;
        case GLUT_KEY_DOWN: cameraPitch+=angleSpeed; break;
        case GLUT_KEY_LEFT: cameraYaw-=angleSpeed; break;
        case GLUT_KEY_RIGHT: cameraYaw+=angleSpeed; break;
        }
    }
    else {
        switch ( key ) {
        case GLUT_KEY_LEFT:
            alpha-=0.1f;
            break;
        case GLUT_KEY_RIGHT:
            alpha+=0.1f;
            break;
        case GLUT_KEY_UP:
            beta+=0.1f;
            break;
        case GLUT_KEY_DOWN:
            beta-=0.1f;
            break;
        }
    }
    glutPostRedisplay( );
}

// change!!!!!
void keyboard(unsigned char key,int x,int y) {
    if ( CameraType ) {
        float speed=0.1f;
        float yawRad=cameraYaw * M_PI / 180.0f;
        float pitchRad=cameraPitch * M_PI / 180.0f;

        switch ( key ) {
        case 'w':
            cameraX+=speed * sin(yawRad);
            cameraZ-=speed * cos(yawRad);
            cameraY-=speed * sin(pitchRad);
            break;
        case 's':
            cameraX-=speed * sin(yawRad);
            cameraZ+=speed * cos(yawRad);
            cameraY+=speed * sin(pitchRad);
            break;
        case 'a':
            cameraX-=speed * cos(yawRad);
            cameraZ-=speed * sin(yawRad);
            break;
        case 'd':
            cameraX+=speed * cos(yawRad);
            cameraZ+=speed * sin(yawRad);
            break;
        case 'v':
            CameraType=false;
            break;
        }
    }
    else {
        switch ( key ) {
        case 'w':
            dist-=1 * distSpeed;
            break;
        case 's':
            dist+=1 * distSpeed;
            break;
        case 'r':
            distSpeed*=2;
            break;
        case 'f':
            distSpeed/=2;
            break;
        case 'e':
            if ( scene + 1 < objPos.size( ) ) {
                scene+=1;
            }
            else {
                scene=0;
            }

            break;
        case 'q':
            if ( scene - 1 >= 0 ) {
                scene-=1;
            }
            else {
                scene=objPos.size( ) - 1;
            }

            break;

        case 'v':
            CameraType=true;
            break;
        }
    }
    
    glutPostRedisplay( );
    
    
}

void draw_eixos(){
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
}

void mouseMotion(int x,int y) {
    if ( CameraType ) {
        static int lastX=-1,lastY=-1;

        if ( lastX == -1 || lastY == -1 ) {
            lastX=x;
            lastY=y;
        }

        int dx=x - lastX;
        int dy=y - lastY;

        cameraYaw+=dx * 0.1f;
        cameraPitch+=dy * 0.1f;

        if ( cameraPitch > 89.0f ) cameraPitch=89.0f;
        if ( cameraPitch < -89.0f ) cameraPitch=-89.0f;

        lastX=x;
        lastY=y;

        glutPostRedisplay( );
    }
    
}

void mouse(int button,int state,int x,int y) {
    if ( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN ) {
        glutMotionFunc(mouseMotion);
    }
    else {
        glutMotionFunc(NULL);
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
    
    if ( scene >= 1 ) {
        lookx=std::get<0>(objPos[ scene ]);
        looky=std::get<1>(objPos[ scene ]);
        lookz=std::get<2>(objPos[ scene ]);
    }

    if ( CameraType ) {
        glRotatef(cameraPitch,1.0f,0.0f,0.0f);
        glRotatef(cameraYaw,0.0f,1.0f,0.0f);

        // Move the camera
        glTranslatef(-cameraX,-cameraY,-cameraZ);
    }
    else {
        gluLookAt(camx,camy,camz,lookx,looky,lookz,upx,upy,upz);
    }

    if(eixos==1){
        draw_eixos();
    }
    
    glColor3f(1.0f, 1.0f, 1.0f); 
    draw();
    
    glutSwapBuffers();
}

void init_vbos(){
    glClearColor(0.0, 0.0, 0.0, 1.0);
    
    // Resize the vbo vector to match the number of triangles
    vbo.resize(numbersArrays.size());

    // Generate buffer IDs for each triangle
    glGenBuffers(numbersArrays.size(), vbo.data());

    // Loop over each triangle
    for (size_t i = 0; i < numbersArrays.size(); i++) {
        // Bind the VBO for the current triangle
        glBindBuffer(GL_ARRAY_BUFFER, vbo[i]);
        // Copy vertex data to the VBO
        glBufferData(GL_ARRAY_BUFFER, numbersArrays[i].size() * sizeof(float), numbersArrays[i].data(), GL_STATIC_DRAW);
    }

    // Unbind the buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void multiplyMatrix(float result[ 16 ],const float matrix[ 16 ]) {
    float temp[ 16 ];
    for ( int i=0; i < 4; ++i ) {
        for ( int j=0; j < 4; ++j ) {
            temp[ i * 4 + j ]=0;
            for ( int k=0; k < 4; ++k ) {
                temp[ i * 4 + j ]+=result[ i * 4 + k ] * matrix[ k * 4 + j ];
            }
        }
    }
    std::copy(temp,temp + 16,result);
}

void translateMatrix(float matrix[ 16 ],float x,float y,float z) {
    float translation[ 16 ]={
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        x, y, z, 1
    };
    multiplyMatrix(matrix,translation);
}

void rotateMatrix(float matrix[ 16 ],float angle,float x,float y,float z) {
    float c=cos(angle * M_PI / 180.0);
    float s=sin(angle * M_PI / 180.0);
    float len=sqrt(x * x + y * y + z * z);
    if ( len != 0 ) {
        x/=len;
        y/=len;
        z/=len;
    }
    float rotation[ 16 ]={
        x * x * ( 1 - c ) + c,     x * y * ( 1 - c ) - z * s, x * z * ( 1 - c ) + y * s, 0,
        y * x * ( 1 - c ) + z * s, y * y * ( 1 - c ) + c,     y * z * ( 1 - c ) - x * s, 0,
        z * x * ( 1 - c ) - y * s, z * y * ( 1 - c ) + x * s, z * z * ( 1 - c ) + c,     0,
        0,                       0,                       0,                       1
    };
    multiplyMatrix(matrix,rotation);
}

void scaleMatrix(float matrix[ 16 ],float x,float y,float z) {
    float scale[ 16 ]={
        x, 0, 0, 0,
        0, y, 0, 0,
        0, 0, z, 0,
        0, 0, 0, 1
    };
    multiplyMatrix(matrix,scale);
}

int main(int argc, char **argv) {

    if(argc!=2){
        std::cout << "numero incorreto de argumentos\n";
        return 1;
    }

    tinyxml2::XMLDocument doc;
    std::string xmlFilePath = /*"tests/" +*/ std::string(argv[1]);
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

    glewInit();
    glEnableClientState(GL_VERTEX_ARRAY);
    init_vbos();

    // Required callback registry 
    glutDisplayFunc(renderScene);
    glutIdleFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutSpecialFunc(keyboardSpecial);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);

    // OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

    glutPostRedisplay();

    glutMainLoop();
    return 0;
}
