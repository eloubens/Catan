#include <string>
#include "model.h"
#include <iostream>

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
//auto [resoc, amount] resocGained =
                    

}

