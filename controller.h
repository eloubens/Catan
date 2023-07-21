#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "player.h"
#include "board.h"

enum class Settlement {
    B, // Basement
    H, // House
    T, // Tower
    R  // Road
};
 
class Controller {
    int tileValRolled;
    Color turn = Color::B;
    std::map<Settlement, std::map<Resource,int>> settlementCost; // stores how many resorces each settlement costs
    Player players[4];
    Board board{};


   
    void roll();
    void trade();

 public: 
    Controller();
    void general();
};



#endif