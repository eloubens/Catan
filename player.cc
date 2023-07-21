#include "player.h"

using namespace std;
 
Player::Player(Color color) : color{color} {}
Player::Player(Color color, int buildingPoints, int resocTotal, Dice dice, 
    std::map<Resource, int> resocMap, std::vector<int> occupiedTiles) :
    color{color}, buildingPoints{buildingPoints}, resocTotal{resocTotal}, 
    dice{dice}, resocMap{resocMap}, occupiedTiles{occupiedTiles} {}

int Player::roll() {
    return dice.roll();
}

vector<int>& Player::getOccupiedTiles() {
    return occupiedTiles;
}

void Player::updateResocMap(const pair<Resource, int> &gainedResoc) {
    resocMap[gainedResoc.first] += gainedResoc.second;
}

/*
Color color;
    int buildingPoints = 0, resocTotal = 0;
    Dice dice;
    std::map<Resource, int> resocMap;
    std::vector<int> occupiedTiles;

*/