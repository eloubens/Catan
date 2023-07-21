#ifndef PLAYER_H
#define PLAYER_H
#include <map>
#include <vector>
#include <utility>
#include "resourceEnum.h"
#include "colorEnum.h"
#include "dice.h"

class Player {
    Color color;
    int buildingPoints = 0, resocTotal = 0;
    Dice dice;
    std::map<Resource, int> resocMap;
    std::vector<int> occupiedTiles;
 public:
    explicit Player(Color color);
    Player(Color color, int buildingPoints, int resocTotal, Dice dice, 
        std::map<Resource, int> resocMap, std::vector<int> occupiedTiles);
    
    void updateResocMap(const std::pair<Resource, int> &gainedResoc);

    std::vector<int>& getOccupiedTiles();
    int roll(); //returns tilevalue rolled
};


#endif
