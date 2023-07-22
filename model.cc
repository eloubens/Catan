#include "model.h"

const int playerNum = 4;

using namespace std;

Model::Model(ifstream &ifs) : players{Player{Color::B}, Player{Color::R}, Player{Color::O}, Player{Color::Y}},
                             board{ifs} {}


//Liz: Work in progress. Commenting out since not done.

/*
// assumes curTurn has already been removed and read in the Controller xlass
Model::Model(std::ifstream &ifs, bool loadingGame) : 
    players{
        Player{Color::B}, 
        Player{Color::R}, 
        Player{Color::O}, 
        Player{Color::Y}
    },
    board{ifs} {}

<builder0Data>
<builder1Data>
<builder2Data>
<builder3Data>
<board>
<geese>

A builder’s data is printed out as follows:
<numBricks> <numEnergies> <numGlass> <numHeat> <numWifi> r <roads> h <housing>
where <roads> is the number of each road, separated by one space, and <housing> is the list of residences that
have been built, each represented as a pair. Each pair in the list represents the vertex of the residence followed by the letter
representing the residence on it.
For example, the row
1 2 1 2 3 r 16 36 19 h 10 B 15 T 27 H
would be the output for a player with 1 BRICK, 2 ENERGY, 1 GLASS, 2 HEAT, 3 WIFI, the roads 16, 36 and 19 and
residences at vertices 10 (a basement), 15 (a tower) and 27 (a house).
<board> is described in section 3.8.
<geese> is a number between 0 and 18 representing the tile that contains the geese. Traditionally, geese would start on
the Park tile since that tile produces no resources. It is up to you whether they are initially displayed or not before a 7 is rolled.
3.8 Board Layout
For loading and saving a board layout, the following format will be used.
The resources will be printed in the order of the resources on the board with 0 representing BRICK, 1 representing
ENERGY, 2 representing GLASS, 3 representing HEAT, 4 representing WIFI, and 5 representing PARK with each resource
being followed by its value
For example, the board in Figure 3 is
0 3 1 10 3 5 1 4 5 7 3 10 2 11 0 3 3 8 0 2 0 6 1 8 4 12 1 5 4 11 2 4 4 6 2 9 2 9
Note that in the provided files, a tile for PARK will always be followed by the number 7 even though it doesn’t have a value
associated.
While the board is symmetric, it is not symmetric enough to allow an easy formula for the relationship between tiles, edges
and vertices. You will therefore need to come up with some reasonable approach to handle this.
Page 8 of 12
*/

//Liz: Work in progress. Commenting out since not done.

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

