#include <string>
#include "model.h"
#include "colorEnum.h"
#include <iostream>
#include <utility>
#include <vector>
#include <map>

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
            //pSettlements[i].ignore(); // ignores 'r' for road
            // reading in roads
            // cout << "printing" << endl;
            // for (auto &n : pSettlements) {
            //     cout << n.str() << endl;
            // }
            // cout << "printing" << endl;
            while(pSettlements[i] >> veNum) {  // edge num
                //tileNum stores the number of the tile that the road was placed om
                tileNum = this->board.placeValidRoad(to_string(veNum), static_cast<Color>(i));
                players[i].addOccupiedTiles(tileNum);
            }
            pSettlements[i].clear();
            pSettlements[i].ignore();  // ignores 'h' for house
            // pSettlements[i] >> veNum;
            // cout << "HERE" << veNum;
            string r;
            Residence res;
            //getResStr(res)
            while(pSettlements[i] >> veNum) {
                pSettlements[i] >> r;
                cout << "Residence Type: " << r << endl;
                res = getResFromStr(r);
                tileNum = this->board.placeValidRes(to_string(veNum), static_cast<Color>(i), res);
                players[i].addBuildingPoints(static_cast<int>(res));
                players[i].addOccupiedTiles(tileNum);
            }
        }
    }


bool Model::hasEnoughResoc(Color c, variant<Residence, Road> type) {
    return players[static_cast<int>(c)].hasEnoughResoc(settlementCost[type]);
}

// vector<int> Model::findGetRes(string vertexNum) {
// // vertexInt is 0..5 meaning which vertex location in a tile.
//             // res is an integer corresponding to Residence
//             // i is tileNum
//             return vector<int>{res, i, color}; 

//     return board.findGetRes(vertexNum);
// }



// the first tile found to contain componentNum is used. Then need to loop through to get all otehr tiles that 
// have componentNum on them as well -> they will always be after.
// This function only works for a basement of road type. If isVertexNum == true, then adding a basement.
void Model::updatePlayerSettlements(int tileNum, string componentNum, Color c, bool isVertexNum) {
    vector<int> occupTiles{tileNum}; // storing tileNum in vector
    if (!players[static_cast<int>(c)].hasOccupTile(tileNum)) {
        board.addTilesContaining(occupTiles, tileNum + 1, componentNum, isVertexNum); // adds all tiles sharing componentNum excluding tileNum
    }
    for (auto n : occupTiles) {
        players[static_cast<int>(c)].addOccupiedTiles(n);
        //cout << n << endl;
    }
}

bool Model::placeRoad(string edgeNum, Color c) {
    try {
        board.placeRoad(edgeNum, c); // will only catch a vector of occupiedTiles if can build on the tile
    } catch (int tileNum) {
        updatePlayerSettlements(tileNum, edgeNum, c, false); // adds buidling points and occupied tiles
        return true;
    }
   // cout << "Model did not place" << endl;
    return false; // if nothing gets thrown, means that residence was not able to be built on
}

pair<Residence, bool> Model::placeNonBasement(string bVertex, Color c) {
    Residence res;
    bool wasPlaced = false;
    try {
        board.placeNonBasement(bVertex, c); // will only catch a vector of occupiedTiles if can build on the tile
    } catch (Residence r) {
        if (r != Residence::NONE) {
            wasPlaced = true;
            players[static_cast<int>(c)].addBuildingPoints(static_cast<int>(r));
        }
        res = r;
    }
    return {res, wasPlaced}; // putting this outside so compiler doesn't say warning
}

bool Model::placeBasement(string bVertex, Color c, bool isDuringTurn) {
    try {
        board.placeBasement(bVertex, c, isDuringTurn); // will only catch a vector of occupiedTiles if can build on the tile
    } catch (int tileNum) {
        updatePlayerSettlements(tileNum, bVertex, c); // adds buidling points and occupied tiles
        players[static_cast<int>(c)].addBuildingPoints(static_cast<int>(Residence::B));
        return true;
    }
   // cout << "Model did not place" << endl;
    return false; // if nothing gets thrown, means that residence was not able to be built on
}


Tile* Model::getTiles() {
    return board.getTiles();
}

int Model::getBuildingPoints(int i) {
    return players[i].getBuildingPoints(); 
}

Color Model::GetColour(int i){
    return players[i].getColour(); 
}

map<Resource, int>& Model::getResocMap(int i) {
    return players[i].getResocMap(); 
}

map<string, Residence> Model::getVertexResMap(int player) {
    string playerCol = getColorChar(this->players[player].getColour()); 
    map <string, Residence> m;
    for (int j : this->players[player].getOccupiedTiles()) { // all the tiles
        for (int k = 0; k < 6; k++) { // all the vertices
            Vertex * vertex = this->getTiles()[j].getVertexAdr(static_cast<vertexEnum>(k)); 
            if (vertex->getPlayer() == playerCol) {
                m[vertex->getLocation()] = vertex->getRes(); 
            }
        }
    }
    return m; 
}


void Model::save(Color turn, string fileName) {
    ofstream backup{fileName};
    
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
        board.setGeeseTileNum(tile);
        board.setGeeseV2(geeseCurrentTile, false);
        board.setGeeseV2(tile, true);
    }

    //cout << "Geese Tile: " << board.getGeeseTile() << endl;

}

vector<string> Model::getPlayersToStealFrom(Color turn) {
    vector<string> p;
    int geeseTile = board.getGeeseTile();
    string c;

    for (auto n : players) {
        if ((n.hasRes(geeseTile)) && (n.getResocTotal() >= 0) && (n.getColour() != turn)) {
            c = getColorStr(n.getColour());
            // conv enum Color to string
            p.emplace_back(c);
        }
    }

    cout << "players to steal from: " << endl;
    for (auto k : p) {
        cout << k << endl;
    }

    return p;

}

string Model::steal(string curPlayer, string playerToSteal) {
    string c, r;
    for (auto p : players) {
        c = getColorStr(p.getColour()); // enum to str
        if (c == playerToSteal){
            r = p.stealResoc();
        }
    }

    for (auto n : players) {
        c = getColorStr(n.getColour());
        if (c == curPlayer) {
            n.addResoc(r);
        }
    }

    return r;
}

string Model::getDiceType(Color c) {
    string diceType;
    for (auto p : players) {
        if (p.getColour() == c) diceType = p.getDiceType();
    }
    return diceType;
}

bool Model::hasWon(Color turn) {
    return players[static_cast<int>(turn)].getBuildingPoints() >= winningGamePoints;
}


void Model::trade(string curPlayer, string tradePlayer, string give, string take) {
    for (auto p : players) {
        if(getColorStr(p.getColour()) == curPlayer) {
            p.addResoc(take);
            p.removeResoc(give);
        }
        
        if(getColorStr(p.getColour()) == tradePlayer) {
            p.addResoc(give);
            p.removeResoc(take);
        }
    }
}

int Model::fairRoll(Color turn) {
    int rollVal;
    for (auto p : players) {
        if (p.getColour() == turn) {
            rollVal = p.fairRoll();
        }
    }

    return rollVal;
}

bool Model::enoughResoc(string curPlayer, string give) {
    for (auto p : players) {
        if (getColorStr(p.getColour()) == curPlayer) {
            return p.enoughResoc(give);
        }
    }

    return false;
}

bool Model::validSteal(string tradePlayer, string take) {
    for (auto p : players) {
        if (getColorStr(p.getColour()) == tradePlayer) {
            return p.validSteal(take);
        }
    }

    return false;
}

int Model::getGeeseTile() {
    return board.getGeeseTile();
}