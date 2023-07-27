#include "player.h"
#include <iostream> 
#include <string>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include "colorEnum.h"
#include "tile.h"

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

int Player::getResocTotal() { return resocTotal; }

Color Player::getColour() {
    return color;
}

 vector<pair<string, int>> Player::removeHalfResocs() {
    vector<pair<string, int>> resocs;

    int numToLose = resocTotal / 2;

    vector<Resource> allResocs;
    vector<Resource> lostResocs;
    std::map<Resource, int> lostResocsCounts;

    
    // put all currently owned resources from resocMap into a new vector
    for (const auto& pair : resocMap) {
        const Resource& r = pair.first;
        int count = pair.second;

        for (int i = 0; i < count; ++i) {
            allResocs.emplace_back(r);
        }
    }

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng{seed};

    for (int i = 0; i < numToLose; i++) {
        if (allResocs.empty()) {
            break; // Stop if there are no more resources to remove
        }

        // Generate a random index to remove from the allResocs vector
        std::uniform_int_distribution<size_t> dist(0, allResocs.size() - 1);
        size_t indexToRemove = dist(rng);

        // Add the lost resource to the 'lostResocs' vector before erasing it from 'allResocs'
        Resource lost = allResocs[indexToRemove];
        lostResocs.emplace_back(lost);

        // Erase the randomly selected resource from 'allResocs'
        allResocs.erase(allResocs.begin() + indexToRemove);
    }

    int b; // brick
    int e; // energy
    int g; // glass
    int h; // heat
    int w; // wifi
    int p; // park

    for (const auto& r : lostResocs) {
        if (r == Resource::BRICK) ++b;
        else if (r == Resource::ENERGY) ++e;
        else if (r == Resource::GLASS) ++g;
        else if (r == Resource::HEAT) ++h;
        else if (r == Resource::WIFI) ++w;
        else if (r == Resource::PARK) ++p;
        else continue;
    }

    int total = b + e + g + h + w + p;
    resocTotal -= total;

    if (b > 0) {
        resocs.emplace_back(make_pair("BRICK", b));
        resocMap[Resource::BRICK] -= b;
    }

    if (e > 0) {
        resocs.emplace_back(make_pair("ENERGY", e));
        resocMap[Resource::ENERGY] -= e;
    }

    if (g > 0) {
        resocs.emplace_back(make_pair("GLASS", g));
        resocMap[Resource::GLASS] -= g;
    }
    
    if (h > 0) {
        resocs.emplace_back(make_pair("HEAT", h));
        resocMap[Resource::HEAT] -= h;
    }

    if (w > 0) {
        resocs.emplace_back(make_pair("WIFI", w));
        resocMap[Resource::WIFI] -= w;
    }

    if (p > 0) {
        resocs.emplace_back(make_pair("PARK", p));
        resocMap[Resource::PARK] -= p;
    }


    return resocs;
 }
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

bool Player::hasRes(int tileNum) {
    for (auto n : occupiedTiles) {
        if (tileNum == n) {
            return true;
            break;
        }
    }

    return false;
}

string Player::stealResoc() {
    string stolenResoc;

    return stolenResoc;
}


void Player::getStatus(std::ostream &out) {
    out << getColorStr(color) << " has " << buildingPoints << " building points,"; 

    for (const auto& entry : resocMap) {
        if (entry.first == Resource::WIFI) {
            out << " and " << entry.second << " " << getResocLowerCaseStr(entry.first) << "." << endl;; 
        } else {
            out << " " << entry.second << " " << getResocLowerCaseStr(entry.first) << ","; 
        }
    }

    out << getColorStr(color) << " has built:" ;
    for (int i : occupiedTiles) { cout << i << endl; }
}
