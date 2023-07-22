#include <iostream>
#include "controller.h"
#include <fstream>
using namespace std;

int main() {
	// read in input from stdin   
	// figure out how to define board here as
	ifstream ifs{"layout.txt"};
	Board board{ifs};
	// while(true){
	// 	Controller controller{};
	// 	controller.general();
	// }
	
	//just doing testing here
	// Edge test{5};
	// Vertex test2{4};
	// Tile{13, 2, Resource::BRICK, 1, 2, 3, 4, 5,5, 5, 5, 5, 5, 5, 6};
	// Player p{Color::B};


}