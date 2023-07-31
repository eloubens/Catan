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

const int gameWon = 1;
const int eofNoSave = -3;
const int invalidInput = -2;
const int eof = -1;
const int vertexMax = 53;
const int edgeMax = 71;

// returns true if non-normal state
bool Controller::isSpecialState(int n) { return n != 0; }

// sets the Model field of the controller. 
// Loads a board from a file, creates and loads a randomized board, or loads a saved game.
int Controller::setModel(bool canRandomize, bool foundRandomize, unsigned &seed, vector<string> &arg_vec) {
    ostringstream board_oss; 
    if (canRandomize && foundRandomize) {  // means -boardload found and  no -board or -load found
        randomize(board_oss, seed);
        istringstream board_iss{board_oss.str()}; 
        model = make_unique<Model>(board_iss); 
        return 0;
        // TESTING
        // Assume you have a std::unique_ptr<Model> named model
        // Create a new Model instance
        //std::unique_ptr<Model> newModel = std::make_unique<Model>(board_iss);
        // Assign the new Model to the existing unique_ptr
        //model = std::move(newModel);


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
                wasBoardLoad = true;
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
            }
        }
    } else { // read in from the default layout.txt file
        ifstream ifs{"layout.txt"};
        board_oss << ifs.rdbuf();
        istringstream board_file{board_oss.str()};
        model = make_unique<Model>(board_file); 
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
    int state = setModel(canRandomize, foundRandomize, seed, arg_vec);
    if (isSpecialState(state)) { return state; }
    view = make_unique<View>(model.get());
    return 0;
}

int Controller::save(string fileName) {
    model->save(turn, fileName);
    return eof; 
}

bool Controller::isEOF() { return in.eof(); }


int Controller::beginningOfGame() {
    //for (int i = 0; i < 3; i++) {
    // int i = 0;
    // buildDefaultBasements(i, true);
    // buildDefaultBasements(i, true);
    for (int i = 0; i < playerAmount; i++) {
        try {
            i = buildDefaultBasements(i, true);
        } catch (int save) {
            return eof;
        }
    }
    for (int i = playerAmount - 1; i >= 0 ; i--) {
        try {
            i = buildDefaultBasements(i, false);
        } catch (int save) {
            return eof; 
        }
    }
    return 0;
}

// if isInc, means its in the increasing loop
// building Mandatory Basements
int Controller::buildDefaultBasements(int i, bool isInc) {
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
    if(!model->placeBasement(bVertex, c, false)) {
        out << "You cannot build here." << endl;
        if (isInc) {
            i--;
        } else {
            i++;
        }
    }
    return i;
}

void Controller::printStatus(int i) {
    int points = model->getBuildingPoints(i);
    if (points == 1 ) {
        out << getColorStr(model->GetColour(i)) << " has " << model->getBuildingPoints(i) << " building point,"; 
    } else {
        out << getColorStr(model->GetColour(i)) << " has " << model->getBuildingPoints(i) << " building points,"; 
    }
    for (const auto& entry : model->getResocMap(i)) {
        if (entry.first == Resource::WIFI) {
            out << " and " << entry.second << " " << getResocLowerCaseStr(entry.first) << "." << endl;; 
        } else {
            out << " " << entry.second << " " << getResocLowerCaseStr(entry.first) << ","; 
        }
    }
}

// prints residences of player turn
void Controller::printResidences() {
    map <string, Residence> vertexResidenceMap = model->getVertexResMap(static_cast<int>(turn)); 
    out << getColorStr(turn) << " has built:" << endl;
    for (const auto& entry : vertexResidenceMap) {
        out << entry.first << " " << getResStr(entry.second) << endl;
    }
}

int Controller::beginningOfTurn() {
    view->printBoard();
    out << "Builder " << getColorStr(turn) << "'s turn." << endl;
    printStatus(static_cast<int>(turn)); 
    printResidences();
    string cmd;
    out << "Enter load, fair, or roll:" << endl;
    out << "> ";
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

    // dice is rolled
    int rollVal = roll(turn); 
    out << "Dice Rolled: " << rollVal << endl;
    if (rollVal == 7) {
        int s = geese();
        if (s == eof) {
            return eof;
        }
    } else {
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
        if (!didPrint) {
            out << "No builders gained resources." << endl;
        }
    }
    
    return 0;
}

void Controller::printHelp() {
    out << "Valid commands:" << endl << "board" << endl << "status" << endl << "residences" << endl 
    << "build-road <edge#>" << endl << "build-res <housing#>" << endl << "improve <housing#>" << endl 
    << "trade <colour> <give> <take>" << endl << "next" << endl << "save <file>" << endl << "help" << endl;
}

bool Controller::hasWon() {
    return model->hasWon(turn);
}

int Controller::DuringTurn() {
    int numInt;
    string cmd, num;
    while(true) {
        out << "> ";
        if (!(in >> cmd)) { return eof; } // would only fail at eof since cmd is a string
        if (cmd == "next") { break; }
        else if (cmd == "board") { view->printBoard(); }
        else if (cmd == "help") {
            printHelp();
        } else if (cmd == "status") { 
            for (int i = 0; i < playerAmount; i++) {
                printStatus(i);
            }
        } else if (cmd == "save") {
            if (!(in >> cmd)) { 
                in.clear();
                in.ignore();
                return eof;
            }
            //out << cmd;
            save(cmd);
            return eofNoSave;
        } else if (cmd == "trade") {
            if (isSpecialState(trade())) { return eof; }
        } else if (cmd == "residences") {
            printResidences();
        }  else if (cmd == "improve" || cmd == "build-res" || cmd == "build-road") {
            if (!(in >> num)) { 
                return eof; 
            }
            istringstream iss{num};
            if (!(iss >> numInt) || numInt < 0 || 
                (cmd == "build-road" && numInt > edgeMax) || 
                ( cmd != "build-road" && numInt > vertexMax)) {
                out << "Invalid command." << endl;
                continue;
            }
            if (cmd == "build-res") {
                buildRes(num);
            } else if (cmd == "improve") {
                improveRes(num);
            } else if (cmd == "build-road") {
                buildRoad(num);
            }
            if (hasWon()) {
                return gameWon;
            }
        } else {
            out << "Invalid command." << endl;
        }
        // can't improve from a tower to more , can't improve if nothing on vertex
        // check b uilding points for imrpove res and make road commands
        // cannot build road through a vertex of a different residence
        //return gameWon; if building points more than 10
    }
    if (turn == Color::Y) {
        turn = Color::B;
    } else {
        turn = static_cast<Color>(static_cast<int>(turn) + 1);
    }
    return 0;
}


void Controller::buildRoad(string edgeNum) {
    if (!model->hasEnoughResoc(turn, Road::R)) {
        out << "You do not have enough resources." << endl;
        return;
    }
    if (!model->placeRoad(edgeNum, turn)) {
        out << "You cannot build here." << endl;
        return;
    }
    out << "Road Placed." << endl;
}

// To improve a res old today
void Controller::improveRes(string vertexNum) {
    auto [res, wasPlaced] = model->placeNonBasement(vertexNum, turn);
    if (!model->hasEnoughResoc(turn, res)) {
        out << "You do not have enough resources." << endl;
        return;
    }
    if (wasPlaced) {
        out << "Residence Improved." << endl;
    } else {
        out << "You cannot build here." << endl;
    }
}

// for dynamic building of a Basement
void Controller::buildRes(string vertexNum){
    if (!model->hasEnoughResoc(turn, Residence::B)) {
        out << "You do not have enough resources." << endl;
        return;
    }
    if (!model->placeBasement(vertexNum, turn, true)) {
        out << "You cannot build here." << endl;
        return;
    }
    out << "Basement Placed." << endl;
}

//this acts like the main function essentially 
int Controller::general(vector<string> &arg_vec) {
    if (isSpecialState(createController(arg_vec))) { return invalidInput; } // could only return invalidInput here
    while(true) {
        // beginning of game. 
        if (!wasBoardLoad) {
            if (isSpecialState(beginningOfGame())) { return save(); }
        }
        wasBoardLoad = false; // for when a new game starts, was Board will not be applicable anymore
        // game begins
        while(true) {
            if (isSpecialState(beginningOfTurn())) { return save(); }
            int state = DuringTurn();
            if (state == eofNoSave) { return eof; }
            if (state == eof) { 
                return save(); 
                out << "I am je";
            }
            if (state == gameWon) { break; }
        }
        string input;
        // state will always be gameWon here
        do {
            out << "Would you like to play again? " << endl << "> ";
            if (!(cin >> input)) { return eof; } // Doesn't save file here on eof
        } while(input != "yes" && input != "no");
        if (input == "yes") {
            //resetGame(); WRITE THIS FUNCTION
            reset();
            continue;
        }
        if (input == "no") {
            break;
        }
    }
    return 0;
}

int Controller::roll(Color turn) {
    string diceType = model->getDiceType(turn);
    int rollVal;

    if (diceType == "load") {
        while (true) {
            out << "Input a roll between 2 and 12: " << endl <<  "> ";
            if (!(in >> rollVal)) {
                if (in.eof()) return eof;
                in.clear();
                in.ignore();
            }
            if ((rollVal < 2) || (rollVal > 12)) {
                out << "Invalid roll." << endl;
            } else {
                break;
            }

        }
        //model->diceRolledUpdate(rollVal); (should not call from here)
    } else if (diceType == "fair") {
        rollVal = model->fairRoll(turn);
        //model->diceRolledUpdate(rollVal); (should not call from here)
    }

    return rollVal;
}

int Controller::geese() {
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
    int curGeeseTile = model->getGeeseTile();
    out << "Choose where to place the GEESE." << endl << "> ";
    in >> tileNum;
    if (isEOF()) return eof;;

    while (tileNum == curGeeseTile) {
        out << "You cannot place the GEESE here." << endl;
        out << "Choose where to place the GEESE." << endl << "> ";
        in >> tileNum;
        if (isEOF()) return eof;;
    }
   
    model->placeGeese(tileNum);

    // stealing resources
    vector<string> playersSteal = model->getPlayersToStealFrom(turn);
    string curPlayer = getColorStr(turn);
    if (playersSteal.empty()) {
        out << "Builder " << curPlayer << " has no builders to steal from." << endl;
    } else {
        out << "Builder " << curPlayer << " can choose to steal from";

        if (playersSteal.size() == 1) {
            out << " " << playersSteal[0] << "." << endl;
        } else {
            for (auto n : playersSteal) {
                out << " " << n << ",";
            }
            out << "." << endl;
        }
        out << "Choose a builder to steal from." << endl << "> ";
        string toSteal;
        in >> toSteal;
        if (isEOF()) return eof;;
        // check from eof and valid input

        string stolenResoc = model->steal(curPlayer, toSteal);

        out << "Builder " << curPlayer << " steals " << stolenResoc << " from Builder " << toSteal << "." << endl;
    }
    return 0;
}

int Controller::trade() {
    string curPlayer = getColorStr(turn);
    string toTradeWith;
    string give;
    string take;
    string answer;

    in >> toTradeWith >> give >> take;
    if (isEOF()) return eof; 

    out << curPlayer << " offers " << toTradeWith << " one " << give << " for one " << take << "." << endl;
    out << "Does " <<  toTradeWith << " accept this offer?" << endl << "> ";
    in >> answer;
    if (isEOF()) return eof;

    while ((answer != "yes") || (answer != "no")) {
        out << "Does " <<  toTradeWith << " accept this offer?" << endl << "> ";
        in >> answer;
        if (isEOF()) return eof;
    }

    if (answer == "yes") {
        if (model->enoughResoc(curPlayer, give)) {
            if (model->validSteal(toTradeWith, take)) {
                model->trade(curPlayer, toTradeWith, give, take);
            } else {
                out << toTradeWith << " does not have enough resources." << endl;
            }
        } else {
            out << "You do not have enough resources." << endl;
        }
    
    }

    return 0;

}

void Controller::randomize(ostringstream& board_oss, unsigned& seed) {
   
    vector<int> tileVal = {2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12}; // die roll
    // 4 bricks(0), 4 energy(1), 4 glass(2), 3 heat(3), 3 wifi(4), 1 park(5)
    vector<int> tileResource = {0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5}; 
    default_random_engine rng{seed};
    shuffle(tileResource.begin(), tileResource.end(), rng);
    shuffle(tileVal.begin(), tileVal.end(), rng);
    for (int i = 0; i < tilesAmount; i++) {
        board_oss << " " << tileResource[i] << " " << tileVal[i]; 
    } 

}

void Controller::reset() {
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    ostringstream board_oss;

    randomize(board_oss, seed);
    istringstream board_iss{board_oss.str()};
    // Create a new Model instance
    std::unique_ptr<Model> newModel = std::make_unique<Model>(board_iss);
    
    // Assign the new Model to the existing unique_ptr
    model = std::move(newModel);   
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