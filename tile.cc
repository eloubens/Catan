#include <utility>
#include "tile.h"

using namespace std;
 
const int verticesNum = 6, edgesNum = 6;

Tile::Tile(int tileNum, Vertex *v1, Vertex *v2, Vertex *v3, Vertex *v4, Vertex *v5, Vertex *v6, 
            Edge *e1, Edge *e2, Edge *e3, Edge *e4, Edge *e5, Edge *e6) :
            tileNum{tileNum}, vertices{v1, v2, v3, v4, v5, v6}, edges{e1, e2, e3, e4, e5, e6} {}

Vertex *Tile::getVertexAdr(vertexEnum num) {return vertices[static_cast<int>(num)];}
Edge *Tile::getEdgeAdr(edgeEnum num) {return edges[static_cast<int>(num)];}

void Tile::placeAdjVerticesV(vertexEnum vertex, vector<Vertex*> &&adjVertices) {
    vertices[static_cast<int>(vertex)]->setAdjV(move(adjVertices));
}

void Tile::placeAdjEdgesV(vertexEnum vertex, vector<Edge*> &&adjEdges) {
    vertices[static_cast<int>(vertex)]->setAdjE(move(adjEdges));
}

void Tile::placeAdjVerticesE(edgeEnum edge, vector<Vertex*> &&adjVertices) {
    edges[static_cast<int>(edge)]->setAdjV(move(adjVertices));
}

void Tile::placeAdjEdgesE(edgeEnum edge,std::vector<Edge*> &&adjEdges) {
    edges[static_cast<int>(edge)]->setAdjE(move(adjEdges));
}


void Tile::setTileVal(int tileVal) { this->tileValue = tileVal; }

void Tile::setGeese() { isGeese = true; }

// function used in ctor of board (only used when reading in a board)
// Only 1 park is going to be in the board 
bool Tile::setResocSetGeese(Resource resocType) {
    if (resocType == Resource::PARK) {
        setGeese();
    }
    this->resocType = resocType;
    return isGeese;   
}

void Tile::setResoc(Resource resocType) {
    this->resocType = resocType;
}

pair<Resource, int> Tile::evalResoc(int tileValRolled, Color player) const{
    if ((tileValue != tileValRolled) || (resocType == Resource::PARK)) return {Resource::NA, 0};
    int resocTotal = 0;
    for (int i = 0; i < verticesNum; i++) {
        resocTotal += vertices[i]->getResidenceAmount(player);
    }
    return {resocType, resocTotal};
}

bool Tile::isPlaceValidRoad(string edgeNum, Color color) {
    for (int i = 0; i < edgesNum; i++) {
        if (edges[i]->isNum(edgeNum)) {
            edges[i]->setValidRoad(color);
            return true;
        }
    }
    return false;
}

bool Tile::isPlaceValidRes(string vertexNum, Color color, Residence res) {
    for (int i = 0; i < verticesNum; i++) {
        if (vertices[i]->isNum(vertexNum)) {
            vertices[i]->setValidRes(color, res);
            return true;
        }
    }
    return false;
}




/*

int tileNum
int tileValue = 0
Resource resocType
Vertex *vertices[6]
Edge *edges[6]
bool isGeese = false

*/