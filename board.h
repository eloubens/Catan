#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <utility>
#include <fstream>
#include "resourceEnum.h"
#include "colorEnum.h"
#include "tile.h"

using namespace std;
 
class Board {
    //Delete
    Tile tiles[1]; // this is just code I wrote to be able to compile 
    //Delete


 public:
    //Delete
    Board(std::ifstream ifs); // this is just code I wrote to be able to compile 
    //Delete
    std::pair<Resource, int> getResoc(int tileNum, int tileValRolled, Color player) const;
};

#endif