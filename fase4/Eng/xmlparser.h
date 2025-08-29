#ifndef XMLPARSER_H
#define XMLPARSER_H

#include "tinyxml2.h"
#define _USE_MATH_DEFINES
#include <stdlib.h>
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

extern int eixos;
extern int width;
extern int height;
extern double lookx;
extern double looky;
extern double lookz;
extern double upx;
extern double upy;
extern double upz;
extern double fov;
extern double near_;
extern double far_;
extern double camx;
extern double camy;
extern double camz;
extern double alpha; // horizontal
extern double beta;  // vertical
extern double dist;

extern int globlight;
extern int filelight;
extern int norm;
extern int text;

extern std::vector<std::vector<float>> numbersArrays;        
extern std::vector<std::vector<float>> normalsArrays;  
extern std::vector<std::vector<float>> texturesArrays;
extern std::vector<std::string> textures;   
extern std::vector<std::pair<std::string,int>> ficheiros;
extern std::vector<std::pair<std::string,int>> info;
extern std::vector<std::pair<std::vector<std::string>,int>> transf;
extern std::vector<std::pair<std::vector<float>,int>> final;
extern std::vector<int> pais;
extern std::vector<std::vector<float>> luzglobal;
extern std::vector<std::vector<std::vector<float>>> luzfinal;
extern int contador;

class NTree {

public:

    struct TreeNode {
        std::string element;
        std::vector<std::string> value;
        std::vector<TreeNode*> childs;
    };

    struct TreeNode* root;
    NTree( );
    TreeNode* getTree( );
    void AddNode(TreeNode* parent, std::string,std::vector<std::string>);
    void AddNode(TreeNode* parent,std::string);
    void AddNode(TreeNode* parent);
    void PrintAll(TreeNode*);
    void PrintAll();
    void PrintAll(std::string,TreeNode*);
    NTree::TreeNode* getFiles( );
    void FilesRecurssion(NTree::TreeNode*,std::vector<std::pair<int,std::pair<std::vector<std::string>,NTree::TreeNode*>>>&,int);
};


void get_attributes(tinyxml2::XMLElement*);

void traverse_elements(tinyxml2::XMLElement*);

void tree_childs(NTree,tinyxml2::XMLElement*,NTree::TreeNode*);
void get_tree(NTree,tinyxml2::XMLElement*);
void get_transformacoes(tinyxml2::XMLElement*, std::string="Null", int=-1);

#endif

