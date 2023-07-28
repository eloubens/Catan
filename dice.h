#ifndef DICE_H
#define DICE_h
#include <string>

class Dice final {
    std::string type = "load"; // load or fair 
    int rollLoaded();

 public:
    // no ctor needed
    int roll();
    int rollFair();
    void setDice(std::string cmd);
    std::string getDiceType();
};

#endif
