#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <utility>
#include <fstream>
#include "resourceEnum.h"
#include "colorEnum.h"
#include "tile.h"

using namespace std;

extern const int tilesNum;
 
class Board {
    Tile tiles[19]; 

 public:

    Board(std::ifstream &ifs); 

    std::pair<Resource, int> getResoc(int tileNum, int tileValRolled, Color player) const;



};

#endif