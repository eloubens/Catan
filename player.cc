#include "player.h"
#include <iostream> 

using namespace std;

Player::Player(Color color) : color{color}, 
    resocMap{
        {Resource::BRICK, 0},
        {Resource::ENERGY, 0},
        {Resource::GLASS, 0},
        {Resource::HEAT, 0},
        {Resource::WIFI, 0}
    }  {}

Player::Player(istringstream &playerData, Color color) : color{color} {
    int num;
    for (int r = 0; r < resocAmount - 1; r++) {// park isn't included
        playerData >> num;
        resocMap[static_cast<Resource>(r)] = num;
    }
}

void Player::addOccupiedTiles(int tileNum) {
    for (auto num : occupiedTiles) {
        if (num == tileNum) { return; }
    }
    occupiedTiles.emplace_back(tileNum);
}

void Player::setDice(string cmd) {
    dice.setDice(cmd);
}

void Player::addBuildingPoints(int num) { buildingPoints += num; }

/*

Color color
int buildingPoints = 0
int resocTotal = 0
Dice dice
std::map<Resource, int> resocMap
std::vector<int> occupiedTiles

*/



int Player::roll() {
    return dice.roll();
}

void Player::updateResocMap(const pair<Resource, int> &gainedResoc) {
    resocMap[gainedResoc.first] += gainedResoc.second;
}

map<Resource, int>& Player::getResocMap() { return resocMap; }

vector<int>& Player::getOccupiedTiles() { return occupiedTiles; }

