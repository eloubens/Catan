#include "model.h"

const int playerNum = 4;

// Model::Model() : players{Player{Color::B}, Player{Color::R}, Player{Color::O}, Player{Color::Y}},
// board{}
// {}

/*    
    std::map<Settlement, std::map<Resource,int>> settlementCost;
    Player players[4];
    Board board{};
*/ 


void Model::roll(Color turn) {
    int tileValRolled = players[static_cast<int>(turn)].roll();
    if (tileValRolled == 7) {
        // GEESE STUFF HERE 
    }

    // gets resources for each player 
    for (int player = 0; player < playerNum - 1; player++) {
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

