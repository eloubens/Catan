#include <utility>
#include <sstream>
#include <iostream>
#include "tile.h"

using namespace std;
 
const int verticesAmount = 6, edgesAmount = 6;

string Tile::getResource() {
    return getResocStr(resocType);
}

bool Tile::tileHasVE(string componentNum, bool isVertex) {
    if (isVertex) {
        for (int i = 0; i < verticesAmount; i++) {
            if (vertices[i]->isNum(componentNum)) {
                return true;
            }
        }
    } else {
        for (int i = 0; i < edgesAmount; i++) {
            if (edges[i]->isNum(componentNum)) {
                return true;
            }
        }
    }
    return false;
}

void Tile::placeNonBasement(string vertexNum, Color c) {
    for (int i = 0; i < verticesAmount; i++)  {
        vertices[i]->placeNonBasement(vertexNum, c);
        try {
        } catch(Residence r) {
            throw r;
        }
    }
}

void Tile::placeRoad(string edgeNum, Color c) {
    for (int i = 0; i < edgesAmount; i++)  {
        try {
            edges[i]->placeRoad(edgeNum, c);
        } catch(bool isValid) {
            throw isValid;
        }
    }
}

void Tile::placeBasement(string bVertex, Color c, bool isDuringTurn) {
    for (int i = 0; i < verticesAmount; i++)  {
        try {
            vertices[i]->placeBasement(bVertex, c, isDuringTurn);
        } catch(bool isValid) {
            throw isValid;
        }
    }
}

string Tile::getVertex(vertexEnum v) {
    return vertices[static_cast<int>(v)]->getVertex();
}

string Tile::getEdge(edgeEnum e) {
    return edges[static_cast<int>(e)]->getEdge();
}

string Tile::getTileNum() {
    ostringstream oss;
    oss << tileNum; 
    return oss.str(); 
}

string Tile::getTileValue() {
    if (getResource() == "PARK")  {return "  ";}
    ostringstream oss;
    oss << tileValue; 
    return oss.str();  
}

string Tile::getTileValueReg() {
    ostringstream oss;
    oss << tileValue; 
    return oss.str();  
}

// used for save, deals with duplicates
void Tile::addSettlementsLocation(Color c, vector<string> &roads, vector<string> &resNum, vector<Residence> &resType) {
    string location;
    bool foundDuplicate;
    for (int i = 0; i < verticesAmount; i++) {
        foundDuplicate = false;
        if (vertices[i]->isPlayer(c)){
            location = vertices[i]->getLocation();
            for (auto num : resNum) {
                if (num == location) {
                    foundDuplicate = true;
                    break;
                } 
            }
            if (!foundDuplicate) {
                resNum.emplace_back(location);
                resType.emplace_back(vertices[i]->getRes());
            }
        }
    }
    for (int i = 0; i < edgesAmount; i++) {
        foundDuplicate = false;
        if (edges[i]->isPlayer(c)){
            location = edges[i]->getLocation();
            for (auto num : roads) {
                if (num == location) {
                    foundDuplicate = true;
                    break;
                } 
            }
            if (!foundDuplicate) {
                roads.emplace_back(location);
            }
        }
    }
}

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

bool Tile::getGeese() {return isGeese;}

void Tile::setGeese(bool geese) { isGeese = geese; }

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
    for (int i = 0; i < verticesAmount; i++) {
        resocTotal += vertices[i]->getResidenceAmount(player);
    }
    return {resocType, resocTotal};
}

bool Tile::isPlaceValidRoad(string edgeNum, Color color) {
    for (int i = 0; i < edgesAmount; i++) {
        if (edges[i]->isNum(edgeNum)) {
            edges[i]->setValidRoad(color);
            return true;
        }
    }
    return false;
}

bool Tile::isPlaceValidRes(string vertexNum, Color color, Residence res) {
    for (int i = 0; i < verticesAmount; i++) {
        if (vertices[i]->isNum(vertexNum)) {
            vertices[i]->setValidRes(color, res);
            return true;
        }
    }
    return false;
}

string Tile::getResocIntFormat() { return to_string(static_cast<int>(resocType)); }

bool Tile::isRes(string colour) {
    for (auto v : vertices) {
        if (v->isOccupied() && v->getVertex()[0] == colour[0]) return true;
    }
    return false;
}
