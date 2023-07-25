#ifndef MODEL_H
#define MODEL_H
#include <utility>
#include <fstream>
#include <sstream>
#include <map>
#include "player.h"
#include "board.h"
#include "resourceEnum.h"

enum class Settlement {
    B, // Basement
    H, // House
    T, // Tower
    R  // Road
};

class Model{
    // stores how many resorces each settlement costs
    // SET MAP HERE (not in ctor)
    std::map<Settlement, std::map<Resource,int>> settlementCost = {
        { Settlement::B, 
            {
                {Resource::BRICK, 1},
                {Resource::GLASS, 1},
                {Resource::ENERGY, 1},
                {Resource::WIFI, 1}
            }
        }, 
        { Settlement::H, 
            {
                {Resource::GLASS, 2},
                {Resource::HEAT, 3}
            }
        },
        { Settlement::T, 
            {
                {Resource::BRICK, 3},
                {Resource::ENERGY, 2},
                {Resource::GLASS, 2},
                {Resource::WIFI, 1},
                {Resource::HEAT, 2}
            }
        }, 
        { Settlement::R, 
            {
                {Resource::HEAT, 1},
                {Resource::WIFI, 1}
            }
        }
    };

    Player players[4];
    public: 
    Board board;
 public:
    Model(std::istringstream &iss); // for just loading a board (from file or random generated)

    Model(std::vector<std::istringstream> &&pResocs, std::vector<std::istringstream> &&pSettlements, 
                                                    std::istringstream &board ,int geeseTileNum);
    bool placeBasement(std::string bVertex, Color c);                                               
    void roll(Color turn);

    // saves current state of game
    void save(Color turn);


};




#endif