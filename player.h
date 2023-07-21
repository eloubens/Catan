#ifndef PLAYER_H
#define PLAYER_H
#include "colorEnum.h"
#include "resourceEnum.h"
#include <map>
#include <vector>

class Player {
    Color color;
    int buildingPoints = 0, resocTotal = 0;
    std::map<Resource, int> resocMap;
    std::vector<int> occupiedTiles;
 public:
    explicit Player(Color color);
    Player(Color color, int buildingPoints, int resocTotal, std::map<Resource, 
                                int> resocMap, std::vector<int> occupiedTiles);
    
    
    void roll();


};


#endif