#include "tile.h"

using namespace std;

Tile::Tile(int tileNum, int tileValue, Resource resocType, int v1, int v2, int v3, int v4, 
    int v5, int v6, int e1, int e2, int e3, int e4, int e5, int e6, bool isGeese) :
    tileNum{tileNum}, tileValue{tileValue}, resocType{resocType}, 
    vertices{Vertex{v1}, Vertex{v2}, Vertex{v3}, Vertex{v4}, Vertex{v5}, Vertex{v6}}, 
    edges{Edge{e1}, Edge{e2}, Edge{e3}, Edge{e4}, Edge{e5}, Edge{e6}}, isGeese{isGeese} {}