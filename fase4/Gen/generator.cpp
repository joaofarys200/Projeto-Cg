#include "functions.h"

std::string figura;
std::string ficheiro;
float unit;
float radius;
float height;
int slices;
int stacks;
float max_radius;
float min_radius;
int tesselation;
std::string patch;

int main(int argc, char** argv)
{
	if (argc > 1) {
		figura = argv[1];
		if (figura == "plane") {
			if (argc == 5) {
				unit = std::stof(argv[2]);
				slices = std::stoi(argv[3]);
				ficheiro = "tests/"+std::string(argv[4]);
				plane(unit, slices, ficheiro);
			}

			else {
				std::cout << "numero incorreto de argumentos\n";
			}
		}

		else if (figura == "box") {
			if (argc == 5) {
				unit = std::stof(argv[2]);
				slices = std::stoi(argv[3]);
				ficheiro = "tests/"+std::string(argv[4]);
				box(unit, slices, ficheiro);
			}

			else {
				std::cout << "numero incorreto de argumentos\n";
			}

		}

		else if (figura == "cone") {
			if (argc == 7) {
				radius = std::stof(argv[2]);
				height = std::stof(argv[3]);
				slices = std::stoi(argv[4]);
				stacks = std::stoi(argv[5]);
				ficheiro = "tests/"+std::string(argv[6]);
				cone(radius, height, slices, stacks, ficheiro);
			}

			else {
				std::cout << "numero incorreto de argumentos\n";
			}
		}

		else if (figura == "sphere") {
			if (argc == 6) {
				radius = std::stof(argv[2]);
				slices = std::stoi(argv[3]);
				stacks = std::stoi(argv[4]);
				ficheiro = "tests/"+std::string(argv[5]);
				sphere(radius, slices, stacks, ficheiro);
			}

			else {
				std::cout << "numero incorreto de argumentos\n";
			}
		}


		else if (figura =="torus"){
			if (argc == 7){
				max_radius = std::stof(argv[2]);
				min_radius = std::stof(argv[3]);
				slices = std::stoi(argv[4]);
				stacks = std::stoi(argv[5]);
				ficheiro = "tests/"+std::string(argv[6]);
				torus(max_radius, min_radius, slices, stacks, ficheiro);
			}

			else{
				std::cout << "numero incorreto de argumentos\n";	
			}
		}

		else if (figura == "patch"){
			if(argc == 5){
				patch = "patch/"+std::string(argv[2]);
				tesselation = std::stoi(argv[3]);
				ficheiro = "tests/"+std::string(argv[4]);
				bezier_patches(patch, tesselation, ficheiro);

			}

			else{
				std::cout << "numero incorreto de argumentos\n";	
			}
		}


		else {
			std::cout << "figura incorreta\n";
		}


	}

	else {
		std::cout << "numero incorreto de argumentos\n";
	}
}
