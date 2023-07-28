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

    Tile* getTiles();
    Model(std::istringstream &iss); // for just loading a board (from file or random generated)
    void setDice(Color c, std::string cmd);

    Model(std::vector<std::istringstream> &&pResocs, std::vector<std::istringstream> &&pSettlements, 
                                                    std::istringstream &board ,int geeseTileNum);
    bool placeBasement(std::string bVertex, Color c);                                               
    //void roll(Color turn);, no longer needed
    //buildRes(Color c, vertexNum)
    // saves current state of game
    void save(Color turn);
    bool hasEnoughResoc(Color C, std::variant<Residence, Road> type);
    std::vector<std::map<Resource, int>> diceRolledUpdate(int rollVal);

    std::vector<std::pair<std::string, std::vector<std::pair<std::string, int>>>> lostResoc();
    std::vector<std::pair<std::string, int>> numLostResoc();

    void placeGeese(int tile);

    std::vector<std::string> getPlayersToStealFrom();

    std::string steal(std::string curPlayer, std::string playertoSteal);

    bool hasWon(Color turn);
};




#endif