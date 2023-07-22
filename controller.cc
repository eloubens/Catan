#include <utility>
#include <iostream>
#include "controller.h"
 
using namespace std;

Controller::Controller() : {

// // In here call a controller function that deals with all the comand line argumenst for loading a board and gett
// /// getting a file
// // than after we have that information, call Model ctor and give it that file. 

// // here determines if reading in file from standard file, provided file, random generated board, 
// // or if loading a game

}


//this acts like the main function essentially 
void Controller::general() {
    // deal with input 


    
    // Liz: Work in progress. Commented out since not finished

    // Next Day (for me to remember) : 
        // figure out if you can initialize ifstream with string
        // ^ for reading in playerData, want to give it as an istringstream or ifs
        // ^ for board randomization, read into string that has all the data. and then 
        // create a ifs from that string and then give to model. 
        // If can't, then Model and Board should take in an stringstream and when reading in
        // from a file, convert to istringstream by converting to string from ifs and then to 
        // istringstream
    

    
    // CASE 1, 2, 3 will be in an if statement. 

    // CASE 1: creating a model where we're loading a board from a file
    // converting from ifstream to istringstream
    ostringstream oss;
    oss << ifs.rdbuf(); // ifs is the file layout.txt
    string fileContent = oss.str();
    istringstream iss(fileContent);
    model = make_unique<Model>(iss);
    
    // CASE 2: creating a model where we're creating and loading a random generated board
    model = make_unique<Model>(iss); // iss is an istringstream 

    // // CASE 3: creating model where we know we're loading a game
    getline(ifs, turn); // setting field variable
    string playerData;
    getline(ifs, playerData);
    istringstream player1{playerData};
    getline(ifs, playerData);
    istringstream player2{playerData};
    getline(ifs, playerData);
    istringstream player3{playerData};
    getline(ifs, playerData);
    istringstream player4{playerData};
    // ifs now only stores <board>, <geese>, each on seperate line
    model = make_unique<Model>(player1, player2, player3, player4, ifs);
}

void Controller::roll(Color turn) {
    model->roll(turn);
}


/*    
Color turn = Color::DNE;
Model *model
*/ 