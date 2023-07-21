#ifndef TILE_H
#define TILE_H
#include "resourceEnum.h"
#include "colorEnum.h"
#include "component.h"
#include <utility>

class Tile {
    int tileNum, tileValue;
    Resource resocType;
 
    Vertex vertices[6]; // vertices at this tile
    Edge edges[6]; // edges at this tile
    bool isGeese; // if a tile has a goose
    
    void removeGoose();
 public:
    //ctor
    Tile(int tileNum, int tileValue, Resource resocType, int v1, int v2, int v3, int v4, 
        int v5, int v6, int e1, int e2, int e3, int e4, int e5, int e6, bool isGeese = false);
    bool isTileValue(int value) const;
    std::pair<Resource, int> evalResoc(Color color) const;
    void printResidences(Color color) const;
    void checkTileRoad(Color color, int egde) const;
    void checkTileRes(Color color, int vertex, bool isBeginPhase) const;
    void placeGoose();
};

#endif