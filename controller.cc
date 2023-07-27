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

const int eof = 2;
const int invalidInput = 1;

// returns true if bad state
bool Controller::isBadState(int n) { return n!= 0; }

// sets the Model field of the controller. 
// Loads a board from a file, creates and loads a randomized board, or loads a saved game.
int Controller::setModel(bool canRandomize, bool foundRandomize, unsigned &seed, vector<string> &arg_vec) {
    const int numOfTiles = 19;
    ostringstream board_oss; 
    if (canRandomize && foundRandomize) {  // means -boardload found and  no -board or -load found
        vector<int> tileVal = {2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12}; // die roll
        // 4 bricks(0), 4 energy(1), 4 glass(2), 3 heat(3), 3 wifi(4), 1 park(5)
        vector<int> tileResource = {0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5}; 
        default_random_engine rng{seed};
        shuffle(tileResource.begin(), tileResource.end(), rng);
        shuffle(tileVal.begin(), tileVal.end(), rng);
        for (int i = 0; i < numOfTiles; i++) {
            board_oss << " " << tileResource[i] << " " << tileVal[i]; 
        } 
        istringstream board_iss{board_oss.str()}; 
        model = make_unique<Model>(board_iss); 
        // own testing
        //cout << board_oss.str() << endl;
    } else if (!canRandomize) { // means -board or -load found
        int size = arg_vec.size(); 
        for (int i = 0; i < size; i++) {
            // loading board from speicified file
            if (arg_vec[i] == "-board") { 
                i++;
                ifstream ifs{arg_vec[i]};
                //ifstream ifs{arg_vec[i]};
                if (!ifs) {
                    err << "Error: Could not open file" << endl;
                    return invalidInput;
                }
                board_oss << ifs.rdbuf();
                istringstream board_iss(board_oss.str());
                model = make_unique<Model>(board_iss);
                // own testing
                //cout << board_oss.str() << endl;
                return 0;
            } 
            // loading game from specified file 
            else if (arg_vec[i] == "-load") { 
                i++;
                ifstream ifs{arg_vec[i]};
                if (!ifs) {
                    err << "Error: Could not open file" << endl;
                    return invalidInput;
                }
                int turnColor, geeseTileNum;
                string resoc, settlements, board;
                ifs >> turnColor;
                // setting field variable
                turn = static_cast<Color>(turnColor); 
                vector<istringstream> pResocs, pSettlements;
                for (int i = 0; i < playerAmount; i++) {
                    // read until 'r' character representing road
                    getline(ifs, resoc, 'r'); 
                    getline(ifs, settlements);
                    pResocs.emplace_back(istringstream{resoc});
                    pSettlements.emplace_back(istringstream{settlements});
                }
                getline(ifs, board);
                istringstream board_iss{board};
                ifs >> geeseTileNum;
                model = make_unique<Model>(move(pResocs), move(pSettlements), board_iss, geeseTileNum);
                return 0;
                //just for own testing
                // out << turnColor << endl;
                // out << "recocs" << endl;
                // for (auto &n: pResocs) {
                //     out << n.str() << endl;
                // }
                // out << "setlements" << endl;
                // for (auto &n: pSettlements) {
                //     out << n.str() << endl;
                // }
                // out << board << endl;
                // out << geeseTileNum << endl;
            }
        }
    } else { // read in from the default layout.txt file
        
        ifstream ifs{"layout.txt"};
        board_oss << ifs.rdbuf();
        istringstream board_file{board_oss.str()};
        
        model = make_unique<Model>(board_file);
        // for own testing
        // out << board_file.str() << endl;
        
    }
    return 0;
}

int Controller::createController(vector<string> &arg_vec) {
    bool canRandomize = true; // can you random generate a board
    bool foundRandomize = false; // is -generate-board command found
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();

	// setting the seed if specified
    // collecting commands
    int size = arg_vec.size(); 
    for (int i = 0; i < size; i++) {
        if (arg_vec[i] == "-seed") {
            if (i != size - 1) {
                i++; 
                try {
                    seed = stoi(arg_vec[i]);
                } catch (const std::invalid_argument& ex) {
                    err << "Invalid argument: " << ex.what() << endl;
                    return invalidInput;
                }
            }
        } 
        if (arg_vec[i] == "-load" || arg_vec[i] == "-board") { // if -load or -board are specified then we ignore the randomize
			canRandomize = false;
		}
        if (arg_vec[i] == "-random-board") {
            foundRandomize = true; 
        } 
	}
    
    setModel(canRandomize, foundRandomize, seed, arg_vec);
    view = make_unique<View>(model.get());
    return 0;
}

int Controller::save() {
    model->save(turn);
    return eof; 
}

bool Controller::isEOF() { return in.eof(); }


int Controller::beginningOfGame() {
    //for (int i = 0; i < 1; i++) {
    for (int i = 0; i < playerAmount; i++) {
        try {
            i = buildBasements(i, true);
        } catch (int save) {
            return save;
        } 
        
    }
    for (int i = playerAmount - 1; i >= 0 ; i--) {
        try {
            i = buildBasements(i, false);
        } catch (int save) {
            return save;
        } 
        
    }
    return 0;
}

// if isInc, means its in the increasing loop
int Controller::buildBasements(int i, bool isInc) {
    int tester;
    string bVertex; // basement vertex
    Color c;
    c = static_cast<Color>(i);
    out << "Builder " << getColorStr(c) << ", where do you want to build a basement?" << endl << "> ";
    if (!(in >> tester)) { 
        if (isEOF()) { throw save(); }
        in.clear();
        in.ignore();
        out << "You cannot build here." << endl;
        if (isInc) {
            i--;
        } else {
            i++;
        }
        return i;
    } // checks for invalid input and invalid vertex
    bVertex = to_string(tester);
    if(!model->placeBasement(bVertex, c)) {
        out << "You cannot build here." << endl;
        if (isInc) {
            i--;
        } else {
            i++;
        }
    }
    return i;
}

int Controller::beginningOfTurn() {
    view->printBoard();
    out << "Builder " << getColorStr(turn) << "'s turn." << endl << "> ";
    // HERE NEED TO ADD CODE TO PRINT OUT THE STATUS OF THE BUILDER WHOS TURN IT IS (in variable turn)!!!!!!!!!
    string cmd;
    while(!(in >> cmd) || (cmd != "roll")) {
        if (isEOF()) { return eof; }
        if (cmd == "load") {
            out << "Dice set to load." << endl;
            model->setDice(turn, cmd);
        }
        if (cmd == "fair") {
            model->setDice(turn, cmd);
            out << "Dice set to fair." << endl;
        }
        out << "> ";
    } 

    // ANYTIME YOU USE in >>. Must use isEOF() command and return oef if true

    // deal with loading the dice here (fair + loaded)

    int rollVal = 6; // value of the dice rolled. This reperesents the tilevalue
    
    // vector (size 4) of a map.
    vector<map<Resource, int>> resocMap = model->diceRolledUpdate(rollVal);
    bool didPrint = false;
    for (int i = 0; i < playerAmount; i++) {
        if (resocMap[i].size() == 0 ) { continue; }
        if (didPrint != true ) { didPrint = true; }
        out << "Builder " << getColorStr(static_cast<Color>(i)) << " gained:" << endl;
        for (auto [resoc, resocNum] : resocMap[i]) {
            out << resocNum << " " << getResocStr(resoc) << endl;
        }
    }
    //vector<map<Resource, int>> diceRolledUpdate(rollVal); // updates for everyone
    // prints color: then go throughr map. If non have any, then "No builders gained resources"




    //int vertexNum; // the vertex number the user wants to build a basement on
    // Used when build-res command
    //model->buildRes(turn, vertexNum);




    return 0;
}

//this acts like the main function essentially 
int Controller::general(vector<string> &arg_vec) {
    int state = createController(arg_vec);
    if (isBadState(state)) { return state; } // could return invalidInput number or could return eof
    // created board by now
    // beginning of game. 
    if (isBadState(beginningOfGame())) { return eof; }
    // game begins
    while(true) {
        if (isBadState(beginningOfTurn())) { return eof; }
        //if (isBadState(DuringGame())) { return eof; }
       break;
    }
    

    
    

    // check for case when trying to impove on empty res!!!!!

    //cout << "printing the board" << endl; 
    //view->printBoard(); 
    return 0;
}



void Controller::roll(Color turn) {
    model->roll(turn);
}

void Controller::geese() {
    // removing half of anyone who has 10+ resources
    vector<pair<string, vector<pair<string, int>>>> v = model->lostResoc();
    vector<pair<string, int>> numLost = model->numLostResoc();
    int i = 0;
    
    for (const auto& p : v) {
        out << "Builder " << p.first << "loses " << numLost[i].second << "resources to the geese. They lose:" << endl;

         for (const auto& resourcePair : p.second) {
            out << resourcePair.second << " " << resourcePair.first << std::endl;
        }
    }

    // placing geese on different tile now
    int tileNum;
    out << "Choose where to place the GEESE" << endl;
    in >> tileNum;
    model->placeGeese(tileNum);

    // stealing resources
    vector<string> playersSteal = model->getPlayersToStealFrom();
    string curPlayer; //= enumToStr(turn);
    out << "Builder " << curPlayer << " can choose to steal from";
    for (auto n : playersSteal) {
        out << " " << n << ",";
    }
    out << endl;
    out << "Choose a builder to steal from." << endl;
    string toSteal;
    in >> toSteal;

    string stolenResoc = model->steal(curPlayer, toSteal);


    // turn var into string
}
/*    
std::ostream &out = std::cout;
std::istream &in = std::cin;
std::ostream &err = std::cerr;
Color turn = Color::B;
std::unique_ptr<Model> model; 
std::unique_ptr<View> view; 
*/ 

/*
    B = 0, // Player 1, Blue
    R = 1, // Player 2, Red
    O = 2, // Player 3, Orange
    Y = 3,  // Player 4, Yellow
*/