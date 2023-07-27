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
 

// 1 means invalid input 

using namespace std;

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
                    return 1;
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
                    return 1;
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
                    return 1;
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

//this acts like the main function essentially 
int Controller::general(vector<string> &arg_vec) {
    int state = createController(arg_vec);
    if (isBadState(state)) { return state; } // if need to terminate program
    view->printBoard(); 
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

    model->steal(curPlayer, toSteal);


    // turn var into string
}
/*    
Color turn = Color::DNE;
Model *model
*/ 