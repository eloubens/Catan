#include <utility>
#include "tile.h"

using namespace std;
 
const int verticesNum = 6, edgesNum = 6;

Tile::Tile(int tileNum, string v1, string v2, string v3, 
    string v4, string v5, string v6, string e1, string e2, string e3, 
    string e4, string e5, string e6) :
    tileNum{tileNum},
    vertices{Vertex{v1}, Vertex{v2}, Vertex{v3}, Vertex{v4}, Vertex{v5}, Vertex{v6}}, 
    edges{Edge{e1}, Edge{e2}, Edge{e3}, Edge{e4}, Edge{e5}, Edge{e6}} {}



Vertex *Tile::getVertexAdr(vertexEnum num) {return &vertices[static_cast<int>(num)];}
Edge *Tile::getEdgeAdr(edgeEnum num) {return &edges[static_cast<int>(num)];}

void Tile::placeAdjVerticesV(vertexEnum vertex, vector<Vertex*> &&adjVertices) {
    vertices[static_cast<int>(vertex)].setAdjV(move(adjVertices));
}

void Tile::placeAdjEdgesV(vertexEnum vertex, vector<Edge*> &&adjEdges) {
    vertices[static_cast<int>(vertex)].setAdjE(move(adjEdges));
}

void Tile::placeAdjVerticesE(edgeEnum edge, vector<Vertex*> &&adjVertices) {
    edges[static_cast<int>(edge)].setAdjV(move(adjVertices));
}

void Tile::placeAdjEdgesE(edgeEnum edge,std::vector<Edge*> &&adjEdges) {
    edges[static_cast<int>(edge)].setAdjE(move(adjEdges));
}


void Tile::setTileVal(int tileVal) {tileValue = tileVal;}

void Tile::setResoc(Resource resocType) {
    if (resocType == Resource::PARK) {
        isGeese = true;
        tileValue = 0;
    }
    resocType = resocType;
}

pair<Resource, int> Tile::evalResoc(int tileValRolled, Color player) const{
    if ((tileValue != tileValRolled) || (resocType == Resource::PARK)) return {Resource::NA, 0};
    int resocTotal = 0;
    for (int i = 0; i < verticesNum; i++) {
        resocTotal += vertices[i].getResidenceAmount(player);
    }
    return {resocType, resocTotal};
}


/*
int tileNum
int tileValue
Resource resocType
Vertex vertices[6]
Edge edges[6]
bool isGeese
*/