#ifndef MODEL_H
#define MODEL_H


#include <utility>
#include <fstream>
#include <map>
#include "player.h"
#include "board.h"
#include "resourceEnum.h"

extern const int playerNum;

enum class Settlement {
    B, // Basement
    H, // House
    T, // Tower
    R  // Road
};

class Model {
    // stores how many resorces each settlement costs
    // SET MAP HERE (not in ctor)
    std::map<Settlement, std::map<Resource,int>> settlementCost = {
        {Settlement::B, {
            {Resource::BRICK, 1},
            {Resource::GLASS, 1},
            {Resource::ENERGY, 1},
            {Resource::WIFI, 1}
        }},
        {Settlement::H, {
            {Resource::GLASS, 2},
            {Resource::HEAT, 3}
        }},
        {Settlement::T, {
            {Resource::BRICK, 3},
            {Resource::ENERGY, 2}
            {Resource::GLASS, 2},
            {Resource::WIFI, 1},
            {Resource::HEAT, 2}
        }}, 
        {Settlement::R, {
            {Resource::HEAT, 1},
            {Resource::WIFI, 1}
        }}
    }



    Player players[4];
    Board board{};
 public:
    Model(std::ifstream ifs, bool loadingGame); // for loading a full game 
    Model(std::ifstream ifs); // for just loading a board

    void roll();


};




#endif