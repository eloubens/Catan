#ifndef DICE_H
#define DICE_h
#include <string>

class Dice final {
    std::string type = "load"; // load or fair 
 public:
    // no ctor needed
    int rollFair();
    void setDice(std::string cmd);
    std::string getDiceType();
};

#endif
