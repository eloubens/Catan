#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <string>
#include <utility>
#include <sstream>
#include "resourceEnum.h"
#include "colorEnum.h"
#include "tile.h"

using namespace std;

extern const int tilesNum;
 
class Board {
    Vertex vertices[54];
    Edge edges[72];
    public:
    Tile tiles[19];
    private:
    int geeseTileNum; 
    

 public:
    Board(std::istringstream &iss, bool isLoadGame = false); 
    Board(std::istringstream &iss, int geeseTileNum);  // when loding game

    std::pair<Resource, int> getResoc(int tileNum, int tileValRolled, Color player) const;

    // returns tileNum that road is on
    int placeValidRoad(std::string edgeNum, Color color);

    // returns tileNum that res is on
    int placeValidRes(std::string vertexNum, Color color, Residence res);
    
};

#endif