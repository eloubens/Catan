#ifndef DICE_H
#define DICE_h
#include <string>

class Dice final {
    std::string type = "load"; // load or fair 
    int rollLoaded();
    int rollFair();
 public:
    // no ctor needed
    int roll();
    void setDice(std::string cmd);
    std::string getDiceType();
};

#endif
