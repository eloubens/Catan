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
    }  { }

Player::Player(istringstream &playerData, Color color) : color{color} {
    int num = 0;
    for (int r = 0; r < resocAmount - 1; r++) {// park isn't included
        playerData >> num;
        resocMap[static_cast<Resource>(r)] = num;
        resocTotal += num;
    }
}

int Player::getBuildingPoints() { return buildingPoints; }

bool Player::hasOccupTile(int tileNum) {
    for (auto num : occupiedTiles) {
        if (num == tileNum) { return true; }
    }
    return false;
}

void Player::addOccupiedTiles(int tileNum) {
    // the original tile found was checked already to be a duplicate by hasOccupTilesu
    // the original tiles shared tiles still might be a duplicate
    for (auto num : occupiedTiles) {
        if (num == tileNum) { return; }
    }
    occupiedTiles.emplace_back(tileNum);
}

void Player::setDice(string cmd) {
    dice.setDice(cmd);
}

void Player::addBuildingPoints(int num) { buildingPoints += num; }

bool Player::hasEnoughResoc(const map<Resource,int> &rMapNeed) {
    for (auto [resoc, amount] : rMapNeed) {
        if (resocMap[resoc] < amount ) { return false; }
    }
    return true;
}

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

        // Adds the lost resource to the 'lostResocs' vector before erasing it from 'allResocs'
        Resource lost = allResocs[indexToRemove];
        lostResocs.emplace_back(lost);

        // Erase the randomly selected resource from 'allResocs'
        allResocs.erase(allResocs.begin() + indexToRemove);
    }

    int b = 0;
    int e = 0;
    int g = 0;
    int h = 0;
    int w = 0;
    int p = 0;


    for (const auto& r : lostResocs) {
        string resoc = getResocStr(r);
        if (resoc == "BRICK") ++b;
        else if (resoc == "ENERGY") ++e;
        else if (resoc == "GLASS") ++g;
        else if (resoc == "HEAT") ++h;
        else if (resoc == "WIFI") ++w;
        else if (resoc == "PARK") ++p;
    }

    //int total = b + e + g + h + w + p;

    if (b > 0) {
        resocs.emplace_back(make_pair("BRICK", b));
        std::pair<Resource, int> lost(Resource::BRICK, b);
        removeResoc(lost);
    }

    if (e > 0) {
        resocs.emplace_back(make_pair("ENERGY", e));
        std::pair<Resource, int> lost(Resource::ENERGY, e);
        removeResoc(lost);
    }

    if (g > 0) {
        resocs.emplace_back(make_pair("GLASS", g));
        std::pair<Resource, int> lost(Resource::GLASS, g);
        removeResoc(lost);
    }
    
    if (h > 0) {
        resocs.emplace_back(make_pair("HEAT", h));
        std::pair<Resource, int> lost(Resource::HEAT, h);
        removeResoc(lost);
    }

    if (w > 0) {
        resocs.emplace_back(make_pair("WIFI", w));
        std::pair<Resource, int> lost(Resource::WIFI, w);
        removeResoc(lost);
    }

    if (p > 0) {
        resocs.emplace_back(make_pair("PARK", p));
        std::pair<Resource, int> lost(Resource::PARK, p);
        removeResoc(lost);
    }
    return resocs;
}

void Player::updateResocMap(const pair<Resource, int> &gainedResoc) {
    resocMap[gainedResoc.first] += gainedResoc.second;
    resocTotal += gainedResoc.second;
}

void Player::removeResoc(const pair<Resource, int> &lostResoc) {
    resocMap[lostResoc.first] -= lostResoc.second;
    resocTotal -= lostResoc.second;
}

map<Resource, int>& Player::getResocMap() { return resocMap; }

vector<int>& Player::getOccupiedTiles() { return occupiedTiles; }

bool Player::hasRes(int tileNum) {
    for (auto n : occupiedTiles) {
        if (tileNum == n) {
            return true;
        }
    }
    return false;
}

string Player::stealResoc() {
    string stolenResoc;
    //int numToLose = 1;
    vector<Resource> allResocs;

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

    // Generate a random index to remove from the allResocs vector
    std::uniform_int_distribution<size_t> dist(0, allResocs.size() - 1);
    size_t indexToRemove = dist(rng);

    // Add the lost resource
    Resource lost = allResocs[indexToRemove];
    stolenResoc = getResocStr(lost);

    std::pair<Resource, int> lostR(lost, 1);
    removeResoc(lostR);
    return stolenResoc;
}

string Player::getDiceType() {
    return dice.getDiceType();
}

int Player::fairRoll() {
    int rollVal = dice.rollFair();
    return rollVal;
}

bool Player::enoughResoc(string give) {
    Resource r = getResocR(give);
    if(resocMap[r] <= 0) return false;
    else return true;
}

bool Player::validSteal(string take) {
    Resource r = getResocR(take);
    if(resocMap[r] <= 0) return false;
    else return true;
}
