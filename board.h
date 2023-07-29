#ifndef BOARD_H
#define BOARD_H
#include <string>
#include <utility>
#include <sstream>
#include "resourceEnum.h"
#include "colorEnum.h"
#include "tile.h"

using namespace std;

extern const int tilesAmount ; // 19

class Board {
    Vertex vertices[54]; // only used to store vertex addresses
    Edge edges[72]; // only used to store edge addresses
    Tile tiles[19];
    int geeseTileNum; 
    // used to cut down on runtime. Not necessary for program to run
    vector<std::string> nonSharedV{"0", "1", "2", "5", "6", "11", "12", "17", "24", "29", 
                                "36", "41", "42", "47", "48", "51", "52", "53"};
    vector<std::string> nonSharedE{"0", "2", "4", "8", "11", "17", "25", "34", "42", "51", "59", "62", "66", "68", "70", 
                                "71", "69", "67", "63", "60", "54", "46", "37", "29", "20", "12", "9", "5", "3", "1"};
    bool isShared(std::string componentNum, bool isVertex);
 public:
    Board(std::istringstream &iss, bool isLoadGame = false); 
    Board(std::istringstream &iss, int geeseTileNum);  // when loding game
    void placeRoad(std::string edgeNum, Color c);
    void placeNonBasement(std::string vertexNum, Color c);
    //vector<int> findGetRes(std::string vertexNum);
    void addTilesContaining(vector<int> &occupTiles, int startingTile, std::string componentNum, bool isVertexNum);
     // returns {Resource::NA, 0} if no resources for the player or {resocType, resocTotal} for the player on tile tileNum
    std::pair<Resource, int> getResoc(int tileNum, int tileValRolled, Color player) const;

    void printBoard(); 
    //string getResource(int n);
    void addSettlementsLocation(int tileNum, Color c, std::vector<std::string> &roads, std::vector<std::string> &resNum, 
                                                            std::vector<Residence> &resType);
    std::string getTileVal(int num); 
    std::string getTileResoc(int num);
    void placeBasement(std::string bVertex, Color c, bool isDuringTurn); 
    int placeValidRoad(std::string edgeNum, Color color);
    int placeValidRes(std::string vertexNum, Color color, Residence res);
    Tile* getTiles(); 


    int getGeeseTile();

    void setGeese(int tileNum, bool geese);
};

#endif