#include <string>
#include "model.h"
#include "colorEnum.h"
#include <iostream>
#include <vector>

using namespace std;

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
/*
Player players[4];
Board board;
*/

void Model::roll(Color turn) {
    int tileValRolled = players[static_cast<int>(turn)].roll();
    if (tileValRolled == 7) {
        // GEESE STUFF HERE 
    }

    // gets resources for each player 
    for (int player = 0; player < playerAmount - 1; player++) {
        vector<int> occupiedTiles = players[player].getOccupiedTiles();
        int vecSize = occupiedTiles.size();
        for (int j = 0; j < vecSize; j++) {
            // gets the number of resources for 1 tile
            const pair<Resource, int> gainedResoc = board.getResoc(occupiedTiles[j], tileValRolled, static_cast<Color>(player));
            if (gainedResoc.second != 0) {
                players[player].updateResocMap(gainedResoc);
            }
        }
    }
}
//auto [resoc, amount] resocGained =

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
        if (n.hasRes(geeseTile)) {
            //c = n.getColour();
            // conv enum Color to string
            p.emplace_back(c);
        }
    }

    return p;

}

void Model::steal(string curPlayer, string playerToSteal) {
    string c;
    vector<Player> stealing;
    for (auto p : players) {
        //c = p.getColour() turn enum into str
        if (c == curPlayer) {

        }
    }
}



