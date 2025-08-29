#include "xmlparser.h"
#include <algorithm> 


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

int globlight=0;
int filelight=0;
int norm=0;
int text=0;

int eixos=1;

std::vector<std::vector<float>> numbersArrays; 
std::vector<std::vector<float>> normalsArrays;  
std::vector<std::vector<float>> texturesArrays;   
std::vector<std::string> textures;   
std::vector<std::pair<std::string,int>> ficheiros;
std::vector<std::pair<std::string,int>> info;
std::vector<std::pair<std::vector<std::string>,int>> transf;
std::vector<std::pair<std::vector<float>,int>> final;
std::vector<int> pais;
std::vector<std::vector<float>> luzglobal; 
std::vector<std::vector<std::vector<float>>> luzfinal;
int contador = 0;

bool filesRecBool, modelList;
NTree::TreeNode* transformation;

void NTree::FilesRecurssion(NTree::TreeNode* parent,std::vector<std::pair<int,std::pair<std::vector<std::string>,NTree::TreeNode*>>>& obPos,int pos) {

    // Recursively process the children of the current node
    if ( !filesRecBool ) {
        transformation=nullptr;
    }
    modelList=false;
    for ( auto* child : parent->childs ) {
        std::vector<std::string> filesChilds={};
        if ( child->element == "transform" ) {
            transformation=child;
            filesRecBool=true;
        }
        else if ( child->element == "models" ) {
            for ( auto* models : child->childs ) {
                filesChilds.push_back(models->value[ 0 ]);
                filesRecBool=false;
            }
            obPos.push_back(make_pair(pos,
                make_pair(filesChilds,transformation)
            )
            );

            transformation=nullptr;
            modelList=true;

        }
        FilesRecurssion(child,obPos,pos + 1);
    }

}

NTree::TreeNode* NTree::getFiles( ) {
    
    if ( NTree::root == nullptr ) {
        return nullptr;
    }
    std::vector<std::pair<int,std::pair<std::vector<std::string>,NTree::TreeNode*>>> obPos;
    NTree::FilesRecurssion(NTree::root, obPos,0);
    
    int base=1000;
    for ( std::pair<int,std::pair<std::vector<std::string>,NTree::TreeNode*>>& i : obPos ) {
        base = std::min(base,i.first);
    }

    NTree::TreeNode* objTree=new TreeNode( );
    objTree->element="root";

    for ( int i=0; i < obPos.size(); i++ ) {
        if ( base == obPos[i].first ) {
            NTree::TreeNode* parent=new TreeNode( );
            parent->element="model";
            parent->value=obPos[ i ].second.first;
            NTree::TreeNode* parent_copy=parent;
            for ( int j=i+1; j < obPos.size( ); j++ ) {
                if ( obPos[ j ].first != base ) {
                    NTree::TreeNode* objChild=new TreeNode( );
                    objChild->element="model";
                    objChild->value=obPos[ j ].second.first;

                    parent_copy->childs.push_back(objChild);
                    parent_copy->childs.push_back(obPos[ j ].second.second);
                    parent_copy=objChild;
                }
                else{
                    break;
                }
            }

            objTree->childs.push_back(parent);
            objTree->childs.push_back(obPos[ i ].second.second);
            
        }
    }

    return objTree;
}

NTree::NTree() {
    NTree::root=new TreeNode( );
}

NTree::TreeNode* NTree::getTree( ) {
    return NTree::root;
}

void NTree::AddNode(TreeNode* parent) {
    TreeNode* node=new TreeNode( );
    NTree::root->childs.push_back(node);
}

void NTree::AddNode(TreeNode* parent, std::string elem) {
    TreeNode* node=new TreeNode( );
    node->element=elem;
    parent->childs.push_back(node);
}

void NTree::AddNode(TreeNode* parent,std::string elem, std::vector<std::string> val) {
    TreeNode* node=new TreeNode( );
    node->element=elem;
    node->value=val;
    parent->childs.push_back(node);
}

void NTree::PrintAll() {
    NTree::PrintAll(NTree::getTree( ));
}

std::string VecStrToStr(std::vector<std::string> val) {
    std::string ret="";
    for ( const std::string& v : val ) {
        ret+=v;
        ret+=", ";
    }
    return ret;
}

void NTree::PrintAll(TreeNode* node) {
    if ( node == nullptr ) {
        return;
    }

    // Print the current node
    std::cout << node->element << "::" << VecStrToStr(node->value) << std::endl;

    // Recursively print all children
    for ( TreeNode* child : node->childs ) {
        NTree::PrintAll("-",child);
    }
}

void NTree::PrintAll(std::string string, TreeNode* node) {
    if ( node == nullptr ) {
        return;
    }

    // Print the current node
    std::cout << string << node->element << "::" << VecStrToStr(node->value) << std::endl;

    // Recursively print all children
    for ( TreeNode* child : node->childs ) {
        NTree::PrintAll(string + "-", child);
    }
}

//função que recebe um elemento xml, e percorre os seus atributos, recolhendo informaçôes referentes à câmara e à janela, 
void get_attributes(tinyxml2::XMLElement* element) { 

    if(std::string(element->Name())=="light"){

        std::vector<float> luz;

        for (const tinyxml2::XMLAttribute* attr = element->FirstAttribute(); attr; attr = attr->Next()) {
            if(std::string(attr->Value())=="directional"){
                luz.push_back(0.0f);
            }

            else if(std::string(attr->Value())=="point"){
                luz.push_back(1.0f);
            }

            else if(std::string(attr->Value())=="spot"){
                luz.push_back(2.0f);
            }

            else{
                luz.push_back(std::stod(attr->Value()));
            }
        }

        luzglobal.push_back(luz);
    }

    else{
    
        for (const tinyxml2::XMLAttribute* attr = element->FirstAttribute(); attr; attr = attr->Next()) {

            if(std::string(element->Name())=="eixos"){
                if(std::string(attr->Value())=="true" ||std::string(attr->Value())=="True"  ){
                    eixos=1;
                }
                else if(std::string(attr->Value())=="false" || std::string(attr->Value())=="False" ){
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
    }

  //  if(luz.size()>0){
    //    luzglobal.push_back(luz);
    //}
    

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
void get_transformacoes(tinyxml2::XMLElement* element, std::string pai, int painum) {

    //recebe como paremetro o identificador do seu pai, que chamou a função recursivamente, e guarda-o no vetor pais
    std::string elementName = element->Name(); 
    int num=contador;
    pais.push_back(painum);
    //caso seja uma transformação, percorre os atributos, e guarda os valores de angle,x,y,z em tranfs. guarda o nome do elemento no vetor info
    if(elementName=="translate" or elementName=="rotate" or elementName=="scale"){ 
        const tinyxml2::XMLAttribute* attr = element->FirstAttribute();

        if(elementName=="translate" && std::string(attr->Name())=="time"){ //caso seja uma transformaçao com tempo (catmull-rom)

            info.push_back(std::make_pair("translatet", contador));         //guardamos o nome da translaçao temporal
            std::vector<std::string> valores;
            int draw=1;
            for (const tinyxml2::XMLAttribute* attr = element->FirstAttribute(); attr; attr = attr->Next()){    //percorremos os seus atributos
                                                                                    
                if(std::string(attr->Name())=="time"){                          //guardamos o valor do tempo*1000
                    std::string time=std::string(attr->Value());
                    float realtime=std::stod(time)*1000;
                    valores.push_back(std::to_string(realtime));                //primeiros 3 valores do vetor nao sao pontos
                }
                else if(std::string(attr->Name())=="align"){                   //se esta alinhado ou nao com a curva
                    valores.push_back(std::string(attr->Value()));
                }
                else if(std::string(attr->Name())=="draw"){                     //caso nao seja necessario renderizar a curva mudamos o valor de draw para 0
                    if(std::string(attr->Value())=="false" || std::string(attr->Value())=="False"){
                        draw=0;
                    }
                }

            }
            for (tinyxml2::XMLElement* child = element->FirstChildElement(); child; child = child->NextSiblingElement()) { //agora percorremos os pontos
                for (const tinyxml2::XMLAttribute* attr2 = child->FirstAttribute(); attr2; attr2 = attr2->Next()){        //e guardamos tudo
                    valores.push_back(std::string(attr2->Value()));
                }
            }
            valores.push_back("0");// variavel current time
            valores.push_back("0");// variavel t
                                                                    //temos que ultimos 6 valores do vetor nao sao pontos 
            valores.push_back("0");// derivada_y.x
            valores.push_back("1");// derivada_y.y
            valores.push_back("0");// derivada_y.z

            valores.push_back(std::to_string(draw));// flag que indica se a curva de catmull roll sera desenhada
            transf.push_back(std::make_pair(valores, contador));

        }


        else if(elementName=="rotate" && std::string(attr->Name())=="time"){    //rotacao temporal
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
            for (const tinyxml2::XMLAttribute* attr = element->FirstAttribute(); attr; attr = attr->Next()){ //rotacao, escala, translacao
                valores.push_back(std::string(attr->Value()));
            }
            transf.push_back(std::make_pair(valores, contador));

        }
        

    }

    //caso seja um ficheiro, guarda o seu path para o vetor ficheiros, e para o vetor info
    else if(elementName=="model"){ 
        const tinyxml2::XMLAttribute* attr = element->FirstAttribute();
        //"../tests/"+std::string(attr->Value())
        info.push_back(std::make_pair("tests/"+std::string(attr->Value()), contador));
        ficheiros.push_back(std::make_pair("tests/"+std::string(attr->Value()), contador));
        tinyxml2::XMLElement* childtext = element->FirstChildElement();
        if(childtext){
            if(std::string(childtext->Name())=="texture"){
                const tinyxml2::XMLAttribute* text = childtext->FirstAttribute();  
                textures.push_back("tests/"+std::string(text->Value()));
            }
            
        }

    }


    //caso contrario, apenas guarda o nome do elemento para o vetor info
    else if(elementName!="texture"){
        info.push_back(std::make_pair(std::string(element->Name()), contador));
    }


    contador+=1;
 
    //percorre todos os filhos do elemento e chama recursivamente a função para eles, dando o seu identificador como atributo
    for (tinyxml2::XMLElement* child = element->FirstChildElement(); child != nullptr; child = child->NextSiblingElement()) {
        


        if(std::string(child->Name())=="color"){             

            std::vector<std::vector<float>> luzes;

            for (tinyxml2::XMLElement* child2 = child->FirstChildElement(); child2 != nullptr; child2 = child2->NextSiblingElement()){
                
                std::vector<float> luz;

                for (const tinyxml2::XMLAttribute* attr2 = child2->FirstAttribute(); attr2; attr2 = attr2->Next()){ 
                    
                    luz.push_back(std::stod(attr2->Value()));
                }
                luzes.push_back(luz);
            }
            luzfinal.push_back(luzes);
        }


        else if(std::string(child->Name())!="texture"){
            get_transformacoes(child, elementName,num); 
        }
    }
}

// funcao que itera recursivamente entre todos os filhos e faz uma arvore de acordo com essa hierarquia, contendo os valores e os elementos em cada nodo
void tree_childs(NTree tree, tinyxml2::XMLElement* element, NTree::TreeNode* node) {
    // condicao para o root node
    if (node->element.empty( )) {
        std::string elementName=element->Name( );
        node->element=elementName;
    }
    int itr=-1;
    // iteracao pelos filhos
    for ( tinyxml2::XMLElement* child=element->FirstChildElement( ); child != nullptr; child=child->NextSiblingElement( ) ) {
        std::vector<std::string> value;
        bool isTempo=false;
        //recolha dos valores
        for ( const tinyxml2::XMLAttribute* attr=child->FirstAttribute( ); attr; attr=attr->Next( ) ) {
            if ( std::string(attr->Name()) == "time" ) {
                isTempo=true;
            }
            value.push_back(std::string(attr->Value( )));
        }
        //adiciona o valor caso o tiver
        if (!value.empty()) {
            if ( isTempo ) {
                tree.AddNode(node,child->Name( ) + std::string("t"),value);
            }
            else {
                tree.AddNode(node,child->Name( ),value);
            }
        }
        else {
            if ( isTempo ) {
                tree.AddNode(node,child->Name( ) + std::string("t"));
            }
            else {
                tree.AddNode(node,child->Name( ));
            }
            
        }
        
        itr++;
        tree_childs(tree,child,node->childs[ itr ]);
        
    }
}

void get_tree(NTree tree, tinyxml2::XMLElement* element) {
    tree_childs(tree, element, tree.getTree());
}



