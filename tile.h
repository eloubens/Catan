#ifndef TILE_H
#define TILE_H
#include <utility>
#include <string>
#include "resourceEnum.h"
#include "colorEnum.h"
#include "residenceEnum.h"
#include "component.h"
#include "vertexEnum.h"
#include "edgeEnum.h"

extern const int verticesAmount, edgesAmount;

class Tile {
    Resource resocType;
    int tileNum, tileValue = 0;
    Vertex *vertices[6];
    Edge *edges[6];
    bool isGeese = false;   
    void removeGoose();
 public:
    Tile(int tileNum, Vertex *v1, Vertex *v2, Vertex *v3, Vertex *v4, Vertex *v5, Vertex *v6, 
                        Edge *e1, Edge *e2, Edge *e3, Edge *e4, Edge *e5, Edge *e6);
    std::string getResource();
    std::string getTileNum();
    std::string getTileValue();
    std::string getResocIntFormat();
    std::string getTileValueReg();
    std::string getVertex(vertexEnum v);
    std::string getEdge(edgeEnum e);
    /* returns {Resource::NA, 0} if no resources for the player 
       or {resocType, resocTotal} for the player on the current tile */
    std::pair<Resource, int> evalResoc(int tileValRolled, Color player) const;
    bool tileHasVE(std::string componentNum, bool isVertex);
    Vertex *getVertexAdr(vertexEnum num);
    Edge *getEdgeAdr(edgeEnum num);
    void setTileVal(int tileVal);
    /* function used in ctor of board (only used when reading in a 
       board, not saved game) returns true if a Geese was placed aka
       if resocType == PARK. Possibly places a geese on tile as side effect. */
    bool setResocSetGeese(Resource resocType);
    void setGeese();
    void setGeese(bool geese);
    bool getGeese();
    /* basic setter method
       void findGetRes(std::string vertexNum); */
    void placeNonBasement(std::string vertexNum, Color c);
    void setResoc(Resource resocType);
    void placeAdjVerticesV(vertexEnum vertex, std::vector<Vertex*> &&adjVertices);
    void placeAdjEdgesV(vertexEnum vertex, std::vector<Edge*> &&adjEdges);
    void placeAdjVerticesE(edgeEnum edge, std::vector<Vertex*> &&adjVertices);
    void placeAdjEdgesE(edgeEnum edge,std::vector<Edge*> &&adjEdges);
    void addSettlementsLocation(Color c, std::vector<std::string> &roads, std::vector<std::string> &resNum, std::vector<Residence> &resType);
    /* returns true if edgeNum is an edge in the tile. 
        Also places a road on the edge if found.*/
    bool isPlaceValidRoad(std::string edgeNum, Color color); 
    void placeRoad(std::string edgeNum, Color c);
    /* returns true if vertexNum is an vertex in the tile. 
        Also places a res on the vertex if found.*/
    bool isPlaceValidRes(std::string vertexNum, Color color, Residence res);
    /* throws true if vertex found and basement was placed.
        throws false if vertex found and basement can't be placed.
        doesn't do anything if vertex not found. */
    void placeBasement(std::string bVertex, Color c, bool isDuringTurn); 
    bool isRes();    
};

#endif
