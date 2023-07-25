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
    // helpers for printBoard
    string getResource(int n);
    void update(string & text, int &width, int &pad, int &right_pad, int &left_pad);
    void printTileTop(int prevPad, string v1, string v2, string e);
    void printBar(int prevPad);
    void printTileNum(int prevPad, string e1, string e2, int i);
    void printTileResoc(string text, int prevPad, int i) ;
    void printTileVal(string text, int prevPad, int i);
    void printVertex(string i);
    void printEdge(int prevPad, string i);
    void printSingleBar(int prevPad);
};

#endif