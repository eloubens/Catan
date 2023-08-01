#ifndef MODEL_H
#define MODEL_H
#include <utility>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <variant>
#include "player.h"
#include "board.h"
#include "resourceEnum.h"
#include "roadEnum.h"
#include "colorEnum.h"

using namespace std;
extern const int winningGamePoints;

class Model{
    // stores how many resorces each settlement costs
    std::map<variant<Residence, Road>, std::map<Resource,int>> settlementCost = {
        { Residence::B, 
            {
                {Resource::BRICK, 1},
                {Resource::GLASS, 1},
                {Resource::ENERGY, 1},
                {Resource::WIFI, 1}
            }
        }, 
        { Residence::H, 
            {
                {Resource::GLASS, 2},
                {Resource::HEAT, 3}
            }
        },
        { Residence::T, 
            {
                {Resource::BRICK, 3},
                {Resource::ENERGY, 2},
                {Resource::GLASS, 2},
                {Resource::WIFI, 1},
                {Resource::HEAT, 2}
            }
        }, 
        { Road::R, 
            {
                {Resource::HEAT, 1},
                {Resource::WIFI, 1}
            }
        }
    };
    Player players[4];
    Board board;
 public:
    bool placeRoad(string edgeNum, Color c);
    std::pair<Residence, bool> placeNonBasement(std::string bVertex, Color c);
    std::map<string, Residence> getVertexResMap(int player);
    Tile* getTiles();
    Model(std::istringstream &iss); // for loading a board (from file or random generated)
    void setDice(Color c, std::string cmd);
    void updatePlayerSettlements(int tileNum, std::string componentNum, Color c, bool isVertexNum = true);
    Model(std::vector<std::istringstream> &&pResocs, std::vector<std::istringstream> &&pSettlements, 
                                                    std::istringstream &board ,int geeseTileNum);
    bool placeBasement(std::string bVertex, Color c, bool isDuringTurn);                                               
    void save(Color turn, string fileName);
    bool hasEnoughResoc(Color C, variant<Residence, Road> type);
    vector<map<Resource, int>> diceRolledUpdate(int rollVal);
    bool buildRes(Color turn, string vertexNum, bool isDuringTurn);
    vector<pair<string, vector<pair <string, int>>>> lostResoc();
    vector<pair<string, int>> numLostResoc();
    void addTilesHavingVertex(vector<int> &occupTiles, int startingTile, string bVertex);
    bool isSharedVertex(string bVertex);
    void placeGeese(int tile);
    vector<string> getPlayersToStealFrom(Color turn);
    string steal(string curPlayer, string playertoSteal);
    bool hasWon(Color turn);
    string getDiceType(Color c);
    void trade(string curPlayer, string tradePlayer, string give, string take);
    Color GetColour(int i);
    int getBuildingPoints(int i); 
    map<Resource, int>& getResocMap(int i);
    int fairRoll(Color turn);
    bool enoughResoc(string curPlayer, string give);
    bool validSteal(string tradePlayer, string take);
    int getGeeseTile();
};

#endif
