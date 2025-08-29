#include <IL/il.h> 
#include "xmlparser.h"
#include "catmullrom.h"
//#include <GL/glxew.h>

std::vector<std::string> stored;
std::vector<std::pair<int,int>> mapa;
std::vector<GLuint> vbo(1);
std::vector<GLuint> vbo2(1);
std::vector<GLuint> vbo3(1);
std::vector<std::pair<std::string,int>> te;
std::vector<std::pair<int, std::vector<int>>> fe;
std::vector<GLuint> texturesglu;

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
                                std::vector<float> aux;      

                                if(transf[l].second==info[k].second){                //se encontramos a transformação que procuravamos, obtemos os seus valores 

                                    if(info[k].first=="translate"){
                                        aux.push_back(0);    
                                    }

                                    else if(info[k].first=="rotate"){
                                        aux.push_back(1);                                            
                                    }                                    

                                    else if(info[k].first=="scale"){                    //numero de 0-4 reference a transformacao em causa
                                        aux.push_back(2); 
                                    }

                                    else if(info[k].first=="rotatet"){
                                        aux.push_back(3); 
                                    }
                                    
                                    else if(info[k].first=="translatet"){
                                        aux.push_back(4); 
                                    }                                                                       


                                    for(size_t m=0; m<transf[l].first.size(); m++){

                                        if(transf[l].first[m]=="true" || transf[l].first[m]=="True"){      
                                            aux.push_back(1);
                                        }
                                        else if(transf[l].first[m]=="false" || transf[l].first[m]=="False"){   //transformacao de volares string em float
                                            aux.push_back(0);                                                 //referentes a atributos como alling e draw(extra)
                                        }
                                        else{
                                            aux.push_back(std::stod(transf[l].first[m]));
                                        }
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

        int flag=-1;

        for(int h=0; h<stored.size();h++){    //percorremos o vetor dos ficheiros ja usados, e vemos se ja foi lido e tem os pontos guardados
            if(stored[h]==elem.first){
                flag=h;                       //se sim, obtemos em flag a posicao em que os pontos estao guardados
            }
        }
        
        if(flag==-1){                       //se ainda nao foi lido, prosseguimos normalmente e guardamos os pontos    
            stored.push_back(elem.first);         

            std::ifstream f(elem.first);

            std::vector<float> numbersArray; 
            std::vector<float> normalsArray;
            std::vector<float> texturesArray;

            std::string linha;

            //percorre todas as linhas do ficheiro
            while (std::getline(f, linha)) {
                std::string xstr="";
                std::string normxstr="";
                std::string ystr="";
                std::string normystr="";
                std::string zstr="";
                std::string normzstr="";
                std::string textxstr="";
                std::string textzstr="";
                float x;
                float y;
                float z;
                float normx;
                float normy;
                float normz;
                float textx;
                float textz;
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

                        else if(contador==3){
                            normxstr+=a;
                        }

                        else if(contador==4){
                            normystr+=a;
                        }

                        else if(contador==5){
                            normzstr+=a;
                        }

                        else if(contador==6){
                            textxstr+=a;
                        }

                        else if(contador==7){
                            textzstr+=a;
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

                if(normxstr.size()>0){
                    normx = std::stof(normxstr);
                    normy = std::stof(normystr);
                    normz = std::stof(normzstr);
                    normalsArray.push_back(normx);
                    normalsArray.push_back(normy);
                    normalsArray.push_back(normz);

                }

                if(textxstr.size()>0){
                    textx = std::stof(textxstr);
                    textz = std::stof(textzstr);
                    texturesArray.push_back(textx);
                    texturesArray.push_back(textz);
                }

            }


            numbersArrays.push_back(numbersArray); //guardamos o vetor no vetor de vetores
            normalsArrays.push_back(normalsArray);
            texturesArrays.push_back(texturesArray);
        }

        else{                                       
            std::vector<float> numbersArray;
            numbersArray.push_back(flag);               //se ja foi lido, guardamos no vetor de vetores, um vetor com um elemento, a posicao em que os pontos se
                                                        //encontram no mesmo vetor
            numbersArrays.push_back(numbersArray); 
            if(normalsArrays.size()>0){  
                normalsArrays.push_back(numbersArray);
            }
            if(texturesArrays.size()>0){
                texturesArrays.push_back(numbersArray);
            }
        }


    }

}

/*
GLuint loadTexture(std::string texture_name) {
    GLuint texture_id;
    std::string texture_path = "tests/" + texture_name; 
    unsigned int t, tw, th;
    unsigned char *texData;
    ilGenImages(1, &t);
    ilBindImage(t);
    
    if (!ilLoadImage((ILstring)texture_path.c_str())) {
        printf("Error - Texture file not found: %s\n", texture_path.data());
        exit(1);
    }
    
    tw = ilGetInteger(IL_IMAGE_WIDTH); //erro aqui
    th = ilGetInteger(IL_IMAGE_HEIGHT);
    ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
    texData = ilGetData();
    glGenTextures(1, &texture_id);


    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
    glGenerateMipmap(GL_TEXTURE_2D);
    return texture_id;
}
*/

void loadTextures() {

    for(int u=0; u<textures.size(); u++){
        GLuint texture_id;
        unsigned int t, tw, th;
        unsigned char *texData;
        ilGenImages(1, &t);
        ilBindImage(t);
        
        if (!ilLoadImage((ILstring)textures[u].c_str())) {
            printf("Error - Texture file not found: %s\n", textures[u].data());
            exit(1);
        }
        
        tw = ilGetInteger(IL_IMAGE_WIDTH); 
        th = ilGetInteger(IL_IMAGE_HEIGHT);
        ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
        texData = ilGetData();
        glGenTextures(1, &texture_id);


        glBindTexture(GL_TEXTURE_2D, texture_id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
        glGenerateMipmap(GL_TEXTURE_2D);
        texturesglu.push_back(texture_id);
    }
}

void draw() {

    if(luzglobal.size()>0){

        float ambi[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambi);

        for(int c = 0; c < luzglobal.size(); c++) {
            GLenum currentLight;

            if(c==0){
                currentLight=GL_LIGHT0;
            }

            else if(c==1){
                currentLight = GL_LIGHT1;
            }

            else if(c==2){
                currentLight = GL_LIGHT2;
            }

            else if(c==3){
                currentLight = GL_LIGHT3;
            }

            glEnable(currentLight);

            if(luzglobal[c][0] == 0) { //direction
                GLfloat lightDirection[] = {luzglobal[c][1], luzglobal[c][2], luzglobal[c][3], 0.0f};        
                glLightfv(currentLight, GL_POSITION, lightDirection);


            } else if(luzglobal[c][0] == 1) { //point
                GLfloat lightPosition[] = {luzglobal[c][1], luzglobal[c][2], luzglobal[c][3], 1.0f}; 
                glLightfv(currentLight, GL_POSITION, lightPosition);  


            } else if(luzglobal[c][0] == 2) { // Spot
                GLfloat lightPosition[] = {luzglobal[c][1], luzglobal[c][2], luzglobal[c][3], 1.0f};
                GLfloat spotDirection[] = {luzglobal[c][4], luzglobal[c][5], luzglobal[c][6]};
                GLfloat cutoff[] = {luzglobal[c][7]};
                glLightfv(currentLight, GL_POSITION, lightPosition);
                glLightfv(currentLight, GL_SPOT_DIRECTION, spotDirection);
                glLightfv(currentLight, GL_SPOT_CUTOFF, cutoff);            
            }

        }
    }


    for (size_t i = 0; i < numbersArrays.size(); i++) {    //percorremos todos todos os vetores de pontos no vetor (cada vetor representa um ficheiro .3d)
        
        int reali=i;                                        
        int num=mapa[i].second;                          //posicao no vetor vbo com os pontos para o ficheiro da posição i em numbersarrays

        if(numbersArrays[i].size()==1){                  //se o tamanho do elemento for igual a um, significa que nao tem pontos, mas que aponta para a posição
            reali=numbersArrays[i][0];                   //em que os seus pontos estao
        }  
                                                      //valor da posicao em numbersArrays que tem os pontos do ficheiro guardado em reali
        glPushMatrix();      //empilhamos a matriz identidade na pilha

        //com todas as transformações geométricas feitas, desenhamos os triangulos
 
        for(int k=final.size()-1;k>=0;k--){               //percorremos todas as transformações no vetor das transformações
            
            if(i==final[k].second){                   //se o identificador do ficheiro for igual ao numero do vetor (que representa um ficheiro .3d) procedemos

                //verificamos qual a transformação geométrica em questao e obtemos os valores, efetuando a transformação

                if(final[k].first[0]==0){       //translacao            
                    glTranslatef(final[k].first[1],final[k].first[2],final[k].first[3]);

                }
                else if(final[k].first[0]==1){      //rotacao
                    glRotatef(final[k].first[1],final[k].first[2],final[k].first[3],final[k].first[4]);
                    
                }
                else if(final[k].first[0]==2){      //escala
                    glScalef(final[k].first[1],final[k].first[2],final[k].first[3]);
                    
                }
                
                else if(final[k].first[0]==3){      //rotacao com tempo
                    float tempo=final[k].first[1]*1000;
                    float angulo=glutGet(GLUT_ELAPSED_TIME)*360/tempo;
                    glRotatef(angulo,final[k].first[2],final[k].first[3],final[k].first[4]);
                }
                

                else if(final[k].first[0]==4){     //translacao com tempo (catmull-rom)

                    int tamanho=final[k].first.size();
                    std::vector<std::vector<float>> pontos; 

                    for(int a = 3; a<tamanho-8; a+=3){          //guarda os pontos de controlo no vetor de vetor de floats pontos
                        std::vector<float> ponto;
                        ponto.push_back(final[k].first[a]);
                        ponto.push_back(final[k].first[a+1]);   
                        ponto.push_back(final[k].first[a+2]);
                        pontos.push_back(ponto);
                    }

                    float draw=final[k].first[tamanho-1];           //flag que indica se vai ser desenhado
                    float pos[3];
                    float deriv[3];
                    renderCatmullRomCurve(pos,deriv,pontos,draw);   
                    
                    float time=final[k].first[1];
                    float t=final[k].first[tamanho-5];
                    float current_time=final[k].first[tamanho-6];

                    getGlobalCatmullRomPoint(t, pos, deriv,pontos);

                    glTranslatef(pos[0], pos[1], pos[2]);

                    if(final[k].first[2]==1){      //caso o objeto seja alinhado com a curva

                        float x[3] = {deriv[0], deriv[1], deriv[2]};
                        float y[3];
                        float z[3];
                        float prev_y[3];
                        prev_y[0]=final[k].first[tamanho-4];
                        prev_y[1]=final[k].first[tamanho-3];
                        prev_y[2]=final[k].first[tamanho-2];


                        normalize(x);
                        cross(x, prev_y, z);
                        normalize(z);
                        cross(z,x,y);
                        normalize(y);

                        final[k].first[tamanho-4]=y[0];
                        final[k].first[tamanho-3]=y[1];
                        final[k].first[tamanho-2]=y[2];


                        float m[16];

                        buildRotMatrix(x,y,z,m);

                        glMultMatrixf(m);
                    }


                    float new_time = glutGet(GLUT_ELAPSED_TIME);
                    float diff = new_time - current_time;
                    
                    
                    
                    t += diff/time;
                    current_time = new_time;
                    
                    final[k].first[tamanho-5]=t;;

                    final[k].first[tamanho-6]=current_time;
                    
                }
            }
        } 

        glBindBuffer(GL_ARRAY_BUFFER, vbo[num]);
        glVertexPointer(3, GL_FLOAT, 0, 0);

        glBindBuffer(GL_ARRAY_BUFFER, vbo2[num]);
        glNormalPointer(GL_FLOAT, 0, 0);

        if(luzfinal.size()>0){
            GLfloat dif[]={luzfinal[i][0][0]/255.0f, luzfinal[i][0][1]/255.0f, luzfinal[i][0][2]/255.0f, 1.0f}; 
            GLfloat amb[]={luzfinal[i][1][0]/255.0f, luzfinal[i][1][1]/255.0f, luzfinal[i][1][2]/255.0f, 1.0f};   
            GLfloat spec[]={luzfinal[i][2][0]/255.0f, luzfinal[i][2][1]/255.0f, luzfinal[i][2][2]/255.0f, 1.0f};   
            GLfloat emi[]={luzfinal[i][3][0]/255.0f, luzfinal[i][3][1]/255.0f, luzfinal[i][3][2]/255.0f, 1.0f};
            GLfloat shi=luzfinal[i][4][0];


/*
        std::cout << "dif: " << luzfinal[i][0][0] << ", " << luzfinal[i][0][1] << ", " << luzfinal[i][0][2] << std::endl;
        std::cout << "amb: " << luzfinal[i][1][0] << ", " << luzfinal[i][1][1] << ", " << luzfinal[i][1][2] << std::endl;
        std::cout << "spec: " << luzfinal[i][2][0] << ", " << luzfinal[i][2][1] << ", " << luzfinal[i][2][2] << std::endl;
        std::cout << "emi: " << luzfinal[i][3][0] << ", " << luzfinal[i][3][1] << ", " << luzfinal[i][3][2] << std::endl;
        std::cout << "shi: " << luzfinal[i][4][0] << "\n\n\n\n\n";
*/


            glMaterialfv(GL_FRONT, GL_DIFFUSE, dif);     // Set diffuse material property
            glMaterialfv(GL_FRONT, GL_AMBIENT, amb);     // Set ambient material property
            glMaterialfv(GL_FRONT, GL_SPECULAR, spec);   // Set specular material property
            glMaterialfv(GL_FRONT, GL_EMISSION, emi);   // Set emissive material property
            glMaterialf(GL_FRONT, GL_SHININESS, shi);  // Set shininess material property


        }

        if(textures.size()>0){
            glBindTexture(GL_TEXTURE_2D, texturesglu[i]);
            glBindBuffer(GL_ARRAY_BUFFER, vbo3[num]);
            glTexCoordPointer(2,GL_FLOAT, 0, 0);
        }

         


        glDrawArrays(GL_TRIANGLES, 0, numbersArrays[reali].size() / 3);
        
        if(textures.size()>0){
            glBindTexture(GL_TEXTURE_2D,0);
        }


        glPopMatrix();
        
    }

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
    gluPerspective(fov ,ratio, near_, far_);

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
    //glutPostRedisplay();
}

void keyboard(unsigned char key,int x,int y) {
    switch ( key ) {
    case 'w':
        dist-=0.25; // Move camera forward
        break;
    case 's':
        dist+=0.25; // Move camera backward (optional)
        break;
        // Add more cases for other keys if needed
    }
    glutPostRedisplay( ); // Request display update
}

void draw_eixos(){
    if(luzglobal.size()>0){
        glDisable(GL_LIGHTING);
    }
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
    if(luzglobal.size()>0){
        glEnable(GL_LIGHTING);
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

    if(eixos==1){
        draw_eixos();
    }

    glColor3f(1.0f, 1.0f, 1.0f); 
    draw();
    
    glutSwapBuffers();
}

void init_vbos(){
    glClearColor(0.0, 0.0, 0.0, 1.0);

    int tamanho=0;
    for(int j=0; j<numbersArrays.size(); j++){ 
        if (numbersArrays[j].size()>1){                 //tamanho necessário para o vetor de vbos, ignoramos elementos com comprimento=1, nao tem pontos
            tamanho++;
        }
    }
    
    vbo.resize(tamanho);
    vbo2.resize(tamanho);
    vbo3.resize(tamanho);
    int nrm=0;
    int tx=0;

    // Gerar buffer IDs
    glGenBuffers(tamanho, vbo.data());
    if(normalsArrays.size()>0){
        if(normalsArrays[0].size()>0){
            nrm=1;
            glGenBuffers(tamanho, vbo2.data());
        }
    }
    if(texturesArrays.size()>0){
        if(texturesArrays[0].size()>0){
            tx=1;
            glGenBuffers(tamanho, vbo3.data());
        }
    }

    int countervbo=0;  //indice do vetor de vbos
    
    for (size_t i = 0; i < numbersArrays.size(); i++) {                         //percorremos o vetor

        if (numbersArrays[i].size()>1){                                 //se o elemento tiver pontos, transferimos os dados para o vetor vbo e incrementamos       
            std::pair<int, int> par = std::make_pair(i, countervbo);  //a posicao do vetor vbo

            mapa.push_back(par);                                     //guardamos no vetor mapa os indices correspondentes aos dois vetores

            glBindBuffer(GL_ARRAY_BUFFER, vbo[countervbo]);
            glBufferData(GL_ARRAY_BUFFER, numbersArrays[i].size() * sizeof(float), numbersArrays[i].data(), GL_STATIC_DRAW);

            if(nrm==1){
                glBindBuffer(GL_ARRAY_BUFFER, vbo2[countervbo]);
                glBufferData(GL_ARRAY_BUFFER, normalsArrays[i].size()* sizeof(float), normalsArrays[i].data(), GL_STATIC_DRAW);
            }
            if(tx==1){
                glBindBuffer(GL_ARRAY_BUFFER, vbo3[countervbo]);
                glBufferData(GL_ARRAY_BUFFER, texturesArrays[i].size()* sizeof(float), texturesArrays[i].data(), GL_STATIC_DRAW); 
            }
            countervbo++;
        }

        else{                                                         //se nao tiver pontos
            int val;
            for(int j=0; j<mapa.size();j++){                          //percorremos o vetor de pares mapa

                if(numbersArrays[i][0]==mapa[j].first){               //encontramos o elemento ja guardado que corresponde ao mesmo ficheiro
                    val=mapa[j].second;                                //guardamos em val o valor da posicao do vbo aonde estao os pontos
                    break;
                }
            }
            std::pair<int, int> par = std::make_pair(i, val); //criamos o novos par para o vetor de correspondencia de indices
            mapa.push_back(par);
        }

    }

  //  glBindBuffer(GL_ARRAY_BUFFER, 0);

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
    
    /*
    root=root->FirstChildElement();               // a função que extrai informação sobre transformações 
    while(std::string(root->Name())!="group"){    // só é chamada quando é encontrado o 1º elemento group
        root=root->NextSiblingElement();
    }*/

    NTree xmlTree;
     
    get_tree(xmlTree,root);
    //xmlTree.PrintAll( ); //- print da arvore desde a root
    xmlTree.PrintAll(xmlTree.getFiles( ));
    
    /*
    get_transformacoes(root);  

    organiza_vetores();

    get_numbers();
    for(int x=0; x<textures.size(); x++){
        std::cout<<textures[x]<<"\n";
    }

    //std::cout<<texturesArrays.size()<<"     txtt\n";
    //std::cout<<numbersArrays.size()<<"     haha\n";
    //std::cout<<normalsArrays.size()<<"     hehe\n";
    //std::cout<<luzglobal.size()<<"     hihi\n";

    

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(width, height);
    glutCreateWindow("lcc_gr15_fase4");

    glewInit();
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    init_vbos();


    // Required callback registry 
    glutDisplayFunc(renderScene);
    glutIdleFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutSpecialFunc(keyboardSpecial);
    glutKeyboardFunc(keyboard);

/*
   // OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);    //desenha com linhas
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);     //preenche o objeto todo ao desenhar
    //glEnable(GL_LIGHTING); 
*/
/*
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);



    if(luzglobal.size()>0){
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  
        glEnable(GL_LIGHTING); 
        glEnable(GL_RESCALE_NORMAL);
    }

    else{
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);  
    }
    
    if(textures.size()>0){
        glEnable(GL_COLOR_MATERIAL);
        glEnable(GL_TEXTURE_2D);
        ilInit();
        loadTextures();
    }
    

    glutPostRedisplay();
    
    glutMainLoop(); 
    */
    return 0;
}
