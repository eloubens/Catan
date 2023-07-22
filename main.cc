#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <random>
#include <chrono>
#include "string.h"

using namespace std;

int main(int argc, char * argv[]) {
    vector<string> arg_vec;
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();

    for (int i = 1; i < argc; i++) {
        string arg = argv[i];
        arg_vec.emplace_back(arg); 
	}

	// setting the seed if specified
    for (int i = 0; i < arg_vec.size(); i++) {
        if (arg_vec[i] == "-seed") {
            i++; 
            seed = stoi(arg_vec[i]);
        } if (arg_vec[i] == "layout.txt") { // already exists so no need to check for -random-board or -load commands
			return 0; 
		}
	}

	// setting random board in an ifstream object
	ofstream file; // convert this back to ifstream 
	file.open("layout.txt"); // check contents of the file
	for (int i = 0; i < arg_vec.size(); i++) {
        if (arg_vec[i] == "-random-board") {
            vector<int> tileVal = {2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12}; // die roll
    		vector<int> tileResource = {0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5}; // 4 bricks(0), 4 energy(1), 4 glass(2), 3 heat(3), 3 wifi(4), 1 park(5)
			default_random_engine rng{seed};
    		shuffle( tileResource.begin(), tileResource.end(), rng);
    		shuffle( tileVal.begin(), tileVal.end(), rng);
			for (int i = 0; i < 19; i++) {
				file << " " << tileResource[i] << " " << tileVal[i]; 
			}
        } else if (arg_vec[i] == "-board") {
			i++; 
			ifstream iff{arg_vec[i]};
			for (int i = 0; i < 19 * 2; i++) {
				string s; 
				iff >> s; 
				file << " " << s; 
			}
		} else if (arg_vec[i] == "-load") {
			i++; 
			ifstream iff{arg_vec[i]};
			string s; 
			int count = 5; // we stop until we have read in 5 H's 
			while ((iff >> s) and (count > 0)) {
				if (s == "H") {count--;}
			}
			file << " " << s; 
			for (int i = 0; i < 19 * 2; i++) {
				iff >> s; 
				file << " " << s; 
			}
		}
	}
}

	// read in input from stdin   
	// figure out how to define board here as
 
	// while(true){
	// 	Controller controller{};
	// 	controller.general();
	// }
	
	//just doing testing here
	// Edge test{5};
	// Vertex test2{4};
	// Tile{13, 2, Resource::BRICK, 1, 2, 3, 4, 5,5, 5, 5, 5, 5, 5, 6};
	// Player p{Color::B};
