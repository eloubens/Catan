#include <utility>
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

bool Controller::isSpecialState(int n) { return n != 0; }

/*   sets the Model field of the controller. Loads a board from a file, creates
     and loads a randomized board, or loads a saved game. */
int Controller::setModel(bool canRandomize, bool foundRandomize, unsigned &seed, vector<string> &arg_vec) {
    ostringstream board_oss; 
    if (canRandomize && foundRandomize) {  // means -boardload found and  no -board or -load found
        randomize(board_oss, seed);
        istringstream board_iss{board_oss.str()}; 
        model = make_unique<Model>(board_iss); 
        return 0;
    } else if (!canRandomize) { // -board or -load found
        int size = arg_vec.size(); 
        for (int i = 0; i < size; i++) {
            // loading board from speicified file
            if (arg_vec[i] == "-board") { 
                i++;
                ifstream ifs{arg_vec[i]};
                if (!ifs) {
                    err << "Error: Could not open file" << endl;
                    return invalidInput;
                }
                board_oss << ifs.rdbuf();
                istringstream board_iss(board_oss.str());
                model = make_unique<Model>(board_iss);
                return 0;
            } 
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
    } else { 
        // read in from the default layout.txt file
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

	// setting the seed if specified, collecting commands
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
    } 
    // checks for invalid input and invalid vertex
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

bool Controller::hasWon(Color c) {
    return model->hasWon(c);
}

int Controller::DuringTurn() {
    int numInt;
    string cmd, num;
    while(true) {
        out << "> ";
        if (!(in >> cmd)) { return eof; }
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
            if (hasWon(turn)) {
                return gameWon;
            }
        } else {
            out << "Invalid command." << endl;
        }
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

int Controller::general(vector<string> &arg_vec) {
    if (isSpecialState(createController(arg_vec))) { return invalidInput; } // only return invalidInput here
    while(true) {
        bool gameHasWon = false;
        // beginning of game. 
        if (!wasBoardLoad) {
            if (isSpecialState(beginningOfGame())) { return save(); }
        }
        // checking if a player already has >= 10 building points
        if (wasBoardLoad) {
            for (int i = 0 ; i < playerAmount; i++) {
                if (hasWon(static_cast<Color>(i))) { 
                    gameHasWon = true;
                }
            }
        }
       
        wasBoardLoad = false; // for when a new game starts, was Board will not be applicable anymore
        // game begins
        while(!gameHasWon) {
            if (isSpecialState(beginningOfTurn())) { return save(); }
            int state = DuringTurn();
            if (state == eofNoSave) { return eof; }
            if (state == eof) { 
                return save(); 
            }
            if (state == gameWon) { break; }
        }
        string input;

        // state will be gameWon
        do {
            out << "Would you like to play again? " << endl << "> ";
            if (!(cin >> input)) { return eof; }
        } while(input != "yes" && input != "no");
        if (input == "yes") {
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
    } else if (diceType == "fair") {
        rollVal = model->fairRoll(turn);
    }
    return rollVal;
}

int Controller::geese() {
    // removing half of anyone who has 10+ resources
    vector<pair<string, int>> numLost = model->numLostResoc();
    vector<pair<string, vector<pair<string, int>>>> v = model->lostResoc();

    int i = 0;
    for (const auto& p : v) {
        out << "Builder " << p.first << " loses " << numLost[i].second << " resources to the geese. They lose:" << endl;
         for (const auto& resourcePair : p.second) {
            out << resourcePair.second << " " << resourcePair.first << std::endl;
        }
        ++i;
    }

    // placing geese on different tile 
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
                if (n == playersSteal[playersSteal.size() - 1]) {
                    out << " " << n << "." << endl;
                } else {
                    out << " " << n << ",";
                }
            }
        }
        
        string toSteal;

        while(true) {
            out << "Choose a builder to steal from." << endl << "> ";
            in >> toSteal;
            if (isEOF()) return eof;
            auto it = std::find(playersSteal.begin(), playersSteal.end(), toSteal);
            if (it != playersSteal.end()) break;
            else out << "You cannot choose that builder." << endl;
        }
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
    
    while(true) {
        out << "Does " <<  toTradeWith << " accept this offer?" << endl << "> ";
        in >> answer;
        if (isEOF()) return eof;
        if ((answer == "yes") || (answer == "no")) break;
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
    // Create a new Model and view instance
    model =  make_unique<Model>(board_iss);
    view = make_unique<View>(model.get());
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
