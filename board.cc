#include <iostream>
#include "board.h"
 
using namespace std;

using namespace std;

Board::Board(vector<int, int> layout[], int vertices[], int edges[]) {
    int subArraySize = 6;
    int numCalls = 19;

    for (int i = 0; i < numCalls; ++i) {
        int index = i * (subArraySize + 1);
        Tile(i, layout[i], vertices[index], edges[index], subArraySize);
    }
// this is just code I wrote to be able to compile 
//Delete
Board::Board() : tiles{Tile{13, 2, Resource::BRICK, 1, 2, 3, 4, 5,5, 5, 5, 5, 5, 5, 6}} {} 
//Delete

pair<Resource, int> Board::getResoc(int tileNum, int tileValRolled, Color player) const {
    return tiles[tileNum].evalResoc(tileValRolled, player);
}