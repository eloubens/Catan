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
    std::map<Settlement, std::map<Resource,int>> settlementCost;
    = {
        {B,     }, 
        {H, },
        {T, }, 
        {R, }


    }



    Player players[4];
    Board board{};
 public:
    Model(std::ifstream ifs, bool loadingGame); // for loading a full game 
    Model(std::ifstream ifs); // for just loading a board

    void roll();


};




#endif