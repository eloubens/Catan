#include <utility>
#include <iostream>
#include <vector> 
#include <string>
#include "controller.h"
 
using namespace std;

Controller::Controller() {
    // CASE 1, 2, 3 will be in an if statement. 
// /*
    // CASE 1: creating a model where we're loading a board from a file
    ifstream ifs{"test"};
    // converting from ifstream to istringstream
    ostringstream oss;
    oss << ifs.rdbuf(); // 'ifs' is the file being read in
    string fileContent = oss.str();
    istringstream iss(fileContent);
    model = make_unique<Model>(iss);
    
    // CASE 2: creating a model where we're creating and loading a random generated board
    model = make_unique<Model>(iss); // iss is an istringstream 

    // CASE 3: creating model where we know we're loading a game
    int n;
    ifs >> n;
    turn = static_cast<Color>(n); // setting field variable
    string resoc, settlements;
    vector<istringstream> pResocs, pSettlements; // p stands for player
    for (int i = 0; i < playerAmount; i++) {
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
    // ifs now only stores <board>, <geese>, each on seperate line
    model = make_unique<Model>(move(pResocs), move(pSettlements), board, geeseTileNum);

// */

// A builder’s data is printed out as follows:
// <numBricks> <numEnergies> <numGlass> <numHeat> <numWifi> r <roads> h <housing>
// where <roads> is the number of each road, separated by one space, and <housing> is the list of residences that
// have been built, each represented as a pair. Each pair in the list represents the vertex of the residence followed by the letter
// representing the residence on it.
// For example, the row
// 1 2 1 2 3 r 16 36 19 h 10 B 15 T 27 H
// would be the output for a player with 1 BRICK, 2 ENERGY, 1 GLASS, 2 HEAT, 3 WIFI, the roads 16, 36 and 19 and
// residences at vertices 10 (a basement), 15 (a tower) and 27 (a house).



// In here call a controller function that deals with all the comand line argumenst for loading a board and gett
/// getting a file
// than after we have that information, call Model ctor and give it that file. 

// here determines if reading in file from standard file, provided file, random generated board, 
// or if loading a game

}


//this acts like the main function essentially 
void Controller::general() {
    // deal with input 
    
}

void Controller::roll(Color turn) {
    model->roll(turn);
}


/*    
Color turn = Color::DNE;
Model *model
*/ 