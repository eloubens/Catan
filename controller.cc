#include <utility>
#include <iostream>
#include "controller.h"
 
using namespace std;

// Controller::Controller() : model{

// // In here call a controller function that deals with all the comand line argumenst for loading a board and gett
// /// getting a file
// // than after we have that information, call Model ctor and give it that file. 

// // here determines if reading in file from standard file, provided file, random generated board, 
// // or if loading a game






// } {}


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
    

    /// have ifstream fully created by here ///
    
    // CASE 1: creating a model where we're just loading a board
    // model = make_unqie<Model>(ifs);

    // // CASE 2: creating model where we know we're loading a game
    // getline(ifs, turn);
    // string playerData;
    // getline(ifs, playerData);
    // ifstream player1{playerData};
    // getline(ifs, playerData);
    // ifstream player2{playerData};
    // getline(ifs, playerData);
    // ifstream player3{playerData};
    // getline(ifs, playerData);
    // ifstream player4{playerData};
    //     // ifs now only stores <board>, <geese>, on each line
    // model = make_unique<Model>(player1, player2, player3, player4, ifs);

    //Liz: Work in progress. Commenting out since not done.
}

void Controller::roll(Color turn) {
    model->roll(turn);
}


/*    
Color turn = Color::DNE;
Model *model
*/ 