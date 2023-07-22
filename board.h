#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <utility>
#include <sstream>
#include "resourceEnum.h"
#include "colorEnum.h"
#include "tile.h"

using namespace std;

extern const int tilesNum;
 
class Board {
    Vertex vertices[53];
    Edge edges[70];
    
    Tile tiles[19];
    int geeseTile; 

 public:
    Board(std::istringstream &iss); 
    //Board(std::istringstream &iss, int geeseTile); 

    std::pair<Resource, int> getResoc(int tileNum, int tileValRolled, Color player) const;



};

#endif