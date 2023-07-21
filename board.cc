#include <iostream>
#include "board.h"
 
using namespace std;

// this is just code I wrote to be able to compile 
//Delete
Board::Board() : tiles{Tile{13, 2, Resource::BRICK, 1, 2, 3, 4, 5,5, 5, 5, 5, 5, 5, 6}} {} 
//Delete

pair<Resource, int> Board::getResoc(int tileNum, int tileValRolled, Color player) const {
    return tiles[tileNum].evalResoc(tileValRolled, player);
}