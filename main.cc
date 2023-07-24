#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <random>
#include <chrono>
#include "string.h"
#include "controller.h"

using namespace std;
int main(int argc, char * argv[]) {
    Controller c{}; 
    vector<string> arg_vec;
    // turning command line arguments into strings
    for (int i = 1; i < argc; i++) {
        arg_vec.emplace_back(argv[i]); 
	}
    return c.general(arg_vec);
}

//just doing testing here
// Edge test{5};
// Vertex test2{4};
// Tile{13, 2, Resource::BRICK, 1, 2, 3, 4, 5,5, 5, 5, 5, 5, 5, 6};
// Player p{Color::B};
