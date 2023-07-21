#include <iostream>
#include <fstream>
#include "board.h"
 
using namespace std;


Board::Board(ifstream ifs) {
    int tileVal;
    int r;

    // tile 0
    ifs >> r >> tileVal;
    Tile(0, tileVal, r, 0, 1, 3, 4, 8, 9, 0, 1, 2, 6, 7, 10);
    
    // tile 1
    ifs >> tileVal >> r;
    Tile(1, tileVal, r, 2, 3, 7, 8, 13, 14, 3, 5, 6, 13, 14, 18);
    
    // tile 2
    ifs >> tileVal >> r;
    Tile(2, tileVal, r, 4, 5, 9, 10, 15, 16, 4, 7, 8, 15, 16, 19);

    // tile 3
    ifs >> tileVal >> r;
    Tile(3, tileVal, r, 6, 7, 12, 13, 18, 19, 9, 12, 13, 20, 21, 26);

    // tile 4
    ifs >> tileVal >> r;
    Tile(4, tileVal, r, 8, 9, 14, 15, 20, 21, 10, 14, 15, 22, 23, 27);

    // tile 5
    ifs >> tileVal >> r;
    Tile(5, tileVal, r, 10, 11, 16, 17, 22, 23, 11, 16, 17, 24, 25, 28);

    // tile 6
    ifs >> tileVal >> r;
    Tile(6, tileVal, r, 13, 14, 19, 20, 25, 26, 18, 21, 22, 30, 31, 35);

    // tile 7
    ifs >> tileVal >> r;
    Tile(7, tileVal, r, 15, 16, 21, 22, 27, 28, 19, 23, 24, 32, 33, 36);

    // tile 8
    ifs >> tileVal >> r;
    Tile(8, tileVal, r, 18, 19, 24, 25, 30, 31, 26, 29, 30, 37, 38, 43);
    
    // tile 9
    ifs >> tileVal >> r;
    Tile(9, tileVal, r, 20, 21, 26, 27, 32, 33, 27, 31, 32, 29, 40, 44);

    // tile 10
    ifs >> tileVal >> r;
    Tile(10, tileVal, r, 22, 23, 28, 29, 34, 35, 28, 33, 34, 41, 42, 45);

    // tile 11
    ifs >> tileVal >> r;
    Tile(11, tileVal, r, 25, 26, 31, 32, 37, 38, 35, 38, 39, 47, 48, 52);

    // tile 12
    ifs >> tileVal >> r;
    Tile(12, tileVal, r, 27, 28, 33, 34, 39, 40, 36, 40, 41, 49, 50, 53);

    // tile 13
    ifs >> tileVal >> r;
    Tile(13, tileVal, r, 30, 31, 36, 37, 42, 43, 43, 46, 47, 54, 55, 60);

    // tile 14
    ifs >> tileVal >> r;
    Tile(14, tileVal, r, 32, 33, 38, 39, 44, 45, 44, 48, 49, 56, 57, 61);

    // tile 15
    ifs >> tileVal >> r;
    Tile(15, tileVal, r, 34, 35, 40, 41, 46, 47, 45, 50, 51, 58, 59, 62);
    
    // tile 16
    ifs >> tileVal >> r;
    Tile(16, tileVal, r, 37, 38, 43, 44, 48, 49, 52, 55, 56, 63, 64, 67);

    // tile 17
    ifs >> tileVal >> r;
    Tile(17, tileVal, r, 39, 40, 45, 46, 50, 51, 53, 57, 58, 65, 66, 68);

    // tile 18
    ifs >> tileVal >> r;
    Tile(18, tileVal, r, 44, 45, 49, 50, 52, 53, 61, 64, 65, 69, 70, 71);
}

// this is just code I wrote to be able to compile 
//Delete
Board::Board() : tiles{Tile{13, 2, Resource::BRICK, 1, 2, 3, 4, 5,5, 5, 5, 5, 5, 5, 6}} {} 
//Delete

pair<Resource, int> Board::getResoc(int tileNum, int tileValRolled, Color player) const {
    return tiles[tileNum].evalResoc(tileValRolled, player);
}