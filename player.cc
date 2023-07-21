#include "player.h"

using namespace std;
 
Player::Player(Color color) : color{color} {}
Player::Player(Color color, int buildingPoints, int resocTotal, 
    std::map<Resource, int> resocMap, std::vector<int> occupiedTiles) :
    color{color}, buildingPoints{buildingPoints}, resocTotal{resocTotal}, 
    resocMap{resocMap}, occupiedTiles{occupiedTiles} {}