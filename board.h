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
    Vertex vertices[54]; // only used to store vertex addresses
    Edge edges[72]; // only used to store edge addresses
    Tile tiles[19];
    int geeseTileNum; 
    
 public:
    Board(std::istringstream &iss, bool isLoadGame = false); 
    Board(std::istringstream &iss, int geeseTileNum);  // when loding game

    std::pair<Resource, int> getResoc(int tileNum, int tileValRolled, Color player) const;

    // returns tileNum that road is on
    int placeValidRoad(std::string edgeNum, Color color);

    // returns tileNum that res is on
    int placeValidRes(std::string vertexNum, Color color, Residence res);

    void printBoard(); 
    //string getResource(int n);
    int getGeeseTile();
    void addSettlementsLocation(int tileNum, Color c, std::vector<std::string> &roads, std::vector<std::string> &resNum, 
                                                            std::vector<Residence> &resType);
    std::string getTileVal(int num); 
    std::string getTileResoc(int num);
    void placeBasement(std::string bVertex, Color c); 
    
};

#endif