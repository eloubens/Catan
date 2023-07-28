#include <string>
#include "model.h"
#include "colorEnum.h"
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

const int winningGamePoints = 10;

Model::Model(istringstream &iss) : players{Player{Color::B}, Player{Color::R}, Player{Color::O}, Player{Color::Y}},
                             board{iss} {}

Model::Model(vector<istringstream> &&pResocs, vector<istringstream> &&pSettlements, istringstream &board, int geeseTileNum) :
    players{
        Player{pResocs[0], Color::B}, 
        Player{pResocs[1], Color::R}, 
        Player{pResocs[2], Color::O}, 
        Player{pResocs[3], Color::Y}
    },
    board{board, geeseTileNum} {
        for (int i = 0; i < playerAmount; i++) {
            int veNum, tileNum; //ve means vertex or edge
            pSettlements[i].ignore(); // ignores 'r' for road
            // reading in roads
            while(pSettlements[i] >> veNum) {  // edge num
                //tileNum stores the number of the tile that the road was placed om
                tileNum = this->board.placeValidRoad(to_string(veNum), static_cast<Color>(i));
                players[i].addOccupiedTiles(tileNum);
            }
            pSettlements[i].clear();
            pSettlements[i].ignore();  // ignores 'h' for house
            char r;
            Residence res;
            while(pSettlements[i] >> veNum) {
                pSettlements[i] >> r;
                res = static_cast<Residence>(r);
                tileNum = this->board.placeValidRes(to_string(veNum), static_cast<Color>(i), res);
                players[i].addBuildingPoints(static_cast<int>(res));
                players[i].addOccupiedTiles(tileNum);
            }
        }
    }


bool Model::hasEnoughResoc(Color c, variant<Residence, Road> type) {
    return players[static_cast<int>(c)].hasEnoughResoc(settlementCost[type]);
}

// OLD CODE
// void Model::roll(Color turn) {
//     int tileValRolled = players[static_cast<int>(turn)].roll();
//     if (tileValRolled == 7) {
//         // GEESE STUFF HERE 
//     }

//     // gets resources for each player 
//     for (int player = 0; player < playerAmount - 1; player++) {
//         vector<int> occupiedTiles = players[player].getOccupiedTiles();
//         int vecSize = occupiedTiles.size();
//         for (int j = 0; j < vecSize; j++) {
//             // gets the number of resources for 1 tile
//             const pair<Resource, int> gainedResoc = board.getResoc(occupiedTiles[j], tileValRolled, static_cast<Color>(player));
//             if (gainedResoc.second != 0) {
//                 players[player].updateResocMap(gainedResoc);
//             }
//         }
//     }
// }
//auto [resoc, amount] resocGained =




// returns if you can place a basement or not

// MAKE A CHANGE HERE, SHOULD TAKE IN A VECTOR OF OCCPIED TILES.
bool Model::placeBasement(string bVertex, Color c) {
    try {
        board.placeBasement(bVertex, c); // will only catch a vector of occupiedTiles if can build on the tile
    } catch (const vector<int> &occupTiles) {
        for (auto n : occupTiles) {
            players[static_cast<int>(c)].addOccupiedTiles(n);
            players[static_cast<int>(c)].addBuildingPoints(static_cast<int>(Residence::B));
        }
        return true;
    }
    return false; // if nothing gets thrown, means that residence was not able to be built on
}

Tile* Model::getTiles() {
    return board.getTiles();
}

void Model::save(Color turn) {
    ofstream backup{"backup.sv"};
    
    backup << static_cast<int>(turn) << endl;
    for (int i = 0; i < playerAmount; i++) {
        map<Resource, int> &resocMap = (players[i]).getResocMap();
        for (int j = 0; j < resocAmount - 1; j++) { // park not included
            backup << resocMap[static_cast<Resource>(j)] << " ";
        }
        backup << "r ";
        const vector<int> &occupiedTiles = players[i].getOccupiedTiles();
        vector<string> roads, resNum;
        vector<Residence> resType;
        for (auto tileNum : occupiedTiles) {
            board.addSettlementsLocation(tileNum, static_cast<Color>(i), roads, resNum, resType);
        }
        for (auto edgeNum : roads) {
            backup << edgeNum << " ";
        }
        backup << "h";
        int size = resNum.size();
        for (int i = 0; i < size; i++) {
            backup << " " << resNum[i] << " " << getResStr(resType[i]);
        }
        backup << endl;
    }
    for (int i = 0; i < 19; i++) {
        if (i == 18) {
            backup << board.getTileResoc(i) << " " << board.getTileVal(i) << endl;
            break;
        }
        backup << board.getTileResoc(i) << " " << board.getTileVal(i) << " ";
    }
    backup << to_string((board.getGeeseTile()));
}
void Model::setDice(Color c, string cmd) {
    players[static_cast<int>(c)].setDice(cmd);
}

vector<map<Resource, int>> Model::diceRolledUpdate(int rollVal) {
    vector<map<Resource, int>> pResocsGained{4, map<Resource, int>{}};
    pair<Resource, int> resocGained; // resoc gained of 1 player
    for (int i = 0; i < playerAmount; i++) {
        const vector<int>& occupTiles = players[i].getOccupiedTiles();
        for (auto tileNum : occupTiles) {
            //{Resource::NA, 0}, {resocType, resocTotal}
            resocGained = board.getResoc(tileNum, rollVal, static_cast<Color>(i)); // gets resource gained of 1 player for 1 reasource
            auto [resoc, resocNum] = resocGained;
            if (resocNum != 0) {
                if (pResocsGained[i].count(resoc) == 0) {
                    pResocsGained[i][resoc] = resocNum;
                } else {
                    pResocsGained[i][resoc] += resocNum;
                }
                players[i].updateResocMap(resocGained);
            }
        }
    }
    return pResocsGained;
}

/*
Player players[4];
Board board;
*/

vector<pair<string, vector<pair<string, int>>>> Model::lostResoc() {
    vector<pair<string, vector<pair<string, int>>>> lostResocs;
    for (auto p : players) {
        if (p.getResocTotal() >= 10) {
            vector<pair<string, int>> resocs = p.removeHalfResocs();
            string c;

            if (p.getColour() == Color::B) c = "Blue";
            else if (p.getColour() == Color::O) c = "Orange";
            else if (p.getColour() == Color::R) c = "Red";
            else if (p.getColour() == Color::Y) c = "Yellow";

            lostResocs.emplace_back(make_pair(c, resocs));
        }
    }

    return lostResocs;
}

vector<pair<string, int>> Model::numLostResoc() {
    vector<pair<string, int>> nLost;
    for (auto p : players) {
        if (p.getResocTotal() >= 10) {
            int numLost = p.getResocTotal() / 2;
            string c;

            if (p.getColour() == Color::B) c = "Blue";
            else if (p.getColour() == Color::O) c = "Orange";
            else if (p.getColour() == Color::R) c = "Red";
            else if (p.getColour() == Color::Y) c = "Yellow";

            nLost.emplace_back(make_pair(c, numLost));
        }
    }

    return nLost;

}

void Model::placeGeese(int tile) {
    int geeseCurrentTile = board.getGeeseTile();

    if (tile != geeseCurrentTile) {
        board.setGeese(geeseCurrentTile, false);
        board.setGeese(tile, true);
    }

}

vector<string> Model::getPlayersToStealFrom() {
    vector<string> p;
    int geeseTile = board.getGeeseTile();
    string c;

    for (auto n : players) {
        if ((n.hasRes(geeseTile)) && (n.getResocTotal() >= 1)) {
            //c = n.getColour();
            // conv enum Color to string
            p.emplace_back(c);
        }
    }

    return p;

}

string Model::steal(string curPlayer, string playerToSteal) {
    string c, r;
    for (auto p : players) {
        //c = p.getColour() turn enum into str
        if (c == playerToSteal){
            r = p.stealResoc();
        }
    }


    return "";
}


bool Model::hasWon(Color turn) {
    return players[static_cast<int>(turn)].getBuildingPoints() >= winningGamePoints;
}


