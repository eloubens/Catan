#include <utility>
#include <iostream>
#include <vector> 
#include <sstream>
#include <algorithm>
#include <fstream>
#include <random>
#include <chrono>
#include <string>
#include "controller.h"
 
using namespace std;

Controller::Controller(int argc, char *argv[]) {
    vector<string> arg_vec;
    //bool randomize = true;
    bool randomize;  
    ostringstream board_oss; 
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();

    // reading in command line arguments, converting to string
    for (int i = 1; i < argc; i++) {
        arg_vec.emplace_back(argv[i]); 
	}

	// setting the seed if specified
    int size = arg_vec.size(); 
    for (int i = 0; i < size; i++) {
        if (arg_vec[i] == "-seed") {
            i++; 
            seed = stoi(arg_vec[i]);
        } 
        if (arg_vec[i] == "-load" || arg_vec[i] == "-board") { // if -load or -board are specified then we ignore the randomize
			randomize = false; 
		}
        if (arg_vec[i] == "-random-board") {
            i++; 
            seed = stoi(arg_vec[i]);
        } 

	}
    setModel(randomize, board_oss, seed, arg_vec);
    view = make_unique<View>(model.get());
}

// sets the Model field of the controller. Loads a board from a file, creates and loads a randomized board, or loads a saved game.
void Controller::setModel(bool randomize, ostringstream &board_oss, unsigned &seed, vector<string> &arg_vec) {
    // CREATING AND LOADING RANDOMIZED BOARD //
    if (randomize) { 
        vector<int> tileVal = {2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12}; // die roll
        // 4 bricks(0), 4 energy(1), 4 glass(2), 3 heat(3), 3 wifi(4), 1 park(5)
        vector<int> tileResource = {0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5}; 
        default_random_engine rng{seed};
        shuffle(tileResource.begin(), tileResource.end(), rng);
        shuffle(tileVal.begin(), tileVal.end(), rng);
        for (int i = 0; i < 19; i++) {
            board_oss << " " << tileResource[i] << " " << tileVal[i]; 
        } 
        istringstream board_iss{board_oss.str()}; 
        model = make_unique<Model>(board_iss); 
    } else {
        int size = arg_vec.size(); 
        for (int i = 0; i < size; i++) {
            // LOADING BOARD FROM FILE //
            if (arg_vec[i] == "-board") { 
                i++;
                ifstream ifs{arg_vec[i]};
                if (!ifs) {
                    err << "Error: Could not open file" << endl;
                    exit(1);
                }
                board_oss << ifs.rdbuf();
                istringstream board_iss(board_oss.str());
                model = make_unique<Model>(board_iss);
                break;
            } 
            // LOADING A GAME FROM FILE //
            else if (arg_vec[i] == "-load") { 
                i++;
                ifstream ifs{arg_vec[i]};
                if (!ifs) {
                    err << "Error: Could not open file" << endl;
                    exit(1);
                }
                int n;
                ifs >> n;
                // setting field variable
                turn = static_cast<Color>(n); 
                string resoc, settlements;
                vector<istringstream> pResocs, pSettlements;
                for (int i = 0; i < playerAmount; i++) {
                    // read until 'r' character representing road
                    getline(ifs, resoc, 'r'); 
                    getline(ifs, settlements);
                    pResocs.emplace_back(istringstream{resoc});
                    pSettlements.emplace_back(istringstream{settlements});
                }
                string s;
                getline(ifs, s);
                istringstream board{s};
                int geeseTileNum;
                ifs >> geeseTileNum;
                model = make_unique<Model>(move(pResocs), move(pSettlements), board, geeseTileNum);
                break; 
            }
        }
    }
}

/*
    // just cheking the contents of stringstream 
    cout << board_oss.str() << endl; 
*/

//this acts like the main function essentially 
void Controller::general() {
    
}

void Controller::roll(Color turn) {
    model->roll(turn);
}

/*    
Color turn = Color::DNE;
Model *model
*/ 