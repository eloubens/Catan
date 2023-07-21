#ifndef TILE_H
#define TILE_H
#include <utility>
#include <iostream>
#include "resourceEnum.h"
#include "colorEnum.h"
#include "component.h"

extern const int verticesNum, edgesNum;

class Tile {
    int tileNum, tileValue;
    Resource resocType;
 
    Vertex vertices[6]; // vertices at this tile
    Edge edges[6]; // edges at this tile
    bool isGeese; // if a tile has a goose
    
    void removeGoose();
 public:
    //ctor
    Tile(std::string tileNum, int tileValue, Resource resocType, std::string v1, std::string v2, std::string v3, 
    std::string v4, std::string v5, std::string v6, std::string e1, std::string e2, std::string e3, 
    std::string e4, std::string e5, std::string e6);

    std::pair<Resource, int> evalResoc(int tileValRolled, Color player) const;
    
};


//void printResidences(Color color) const;
    // void checkTileRoad(Color color, int egde) const;
    // void checkTileRes(Color color, int vertex, bool isBeginPhase) const;
    // void placeGoose();
    //bool isTileValue(int value) const;

#endif