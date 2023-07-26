#ifndef PLAYER_H
#define PLAYER_H
#include <map>
#include <vector>
#include <utility>
#include <sstream>
#include "resourceEnum.h"
#include "colorEnum.h"
#include "dice.h"

extern const int numresocType;

class Player {
    Color color;
    //int buildingPoints = 0, resocTotal = 0;
    Dice dice;
    std::map<Resource, int> resocMap;
    std::vector<int> occupiedTiles;
 public:
 int buildingPoints = 0, resocTotal = 0;
    explicit Player(Color color);
    explicit Player(std::istringstream &playerData, Color color);
    int roll(); //returns tilevalue rolled
    // adds tileNum to vector of occupiedTiles, doesn't add it if it already exists
    void addOccupiedTiles(int tileNum);
    void addBuildingPoints(int num);

    void updateResocMap(const std::pair<Resource, int> &gainedResoc);
    std::map<Resource, int>& getResocMap();
    std::vector<int>& getOccupiedTiles();
};

#endif
