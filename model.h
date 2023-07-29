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


extern const int winningGamePoints; // 10

class Model{
    // stores how many resorces each settlement costs
    // SET MAP HERE (not in ctor)
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
    // vector<int> findGetRes(std::string vertexNum);
    void placeNonBasement(std::string bVertex, Color c);
    std::map<string, Residence> getVertexResMap(int player);
    Tile* getTiles();
    Model(std::istringstream &iss); // for just loading a board (from file or random generated)
    void setDice(Color c, std::string cmd);
    void updatePlayerSettlements(int tileNum, std::string componentNum, Color c, Residence r, bool isVertexNum = true);
    Model(std::vector<std::istringstream> &&pResocs, std::vector<std::istringstream> &&pSettlements, 
                                                    std::istringstream &board ,int geeseTileNum);
    bool placeBasement(std::string bVertex, Color c, bool isDuringTurn);                                               
    //void roll(Color turn);, no longer needed
    //buildRes(Color c, vertexNum)
    // saves current state of game
    void save(Color turn, std::string fileName);
    bool hasEnoughResoc(Color C, std::variant<Residence, Road> type);
    std::vector<std::map<Resource, int>> diceRolledUpdate(int rollVal);
    bool buildRes(Color turn, std::string vertexNum, bool isDuringTurn);
    std::vector<std::pair<std::string, std::vector<std::pair<std::string, int>>>> lostResoc();
    std::vector<std::pair<std::string, int>> numLostResoc();
    void addTilesHavingVertex(vector<int> &occupTiles, int startingTile, string bVertex);
    bool isSharedVertex(std::string bVertex);
    void placeGeese(int tile);

    std::vector<std::string> getPlayersToStealFrom(Color turn);

    std::string steal(std::string curPlayer, std::string playertoSteal);

    bool hasWon(Color turn);
    std::string getDiceType(Color c);

    void trade(string curPlayer, string tradePlayer, string give, string take);

    int fairRoll(Color turn);

    bool enoughResoc(std::string curPlayer, std::string give);

    bool validSteal(std::string tradePlayer, std::string take);




};




#endif