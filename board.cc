#include <iostream>
#include "board.h"

using namespace std;

Board::Board(vector<int, int> layout[], int vertices[], int edges[]) {
    int subArraySize = 6;
    int numCalls = 19;

    for (int i = 0; i < numCalls; ++i) {
        int index = i * (subArraySize + 1);
        Tile(i, layout[i], vertices[index], edges[index], subArraySize);
    }
}