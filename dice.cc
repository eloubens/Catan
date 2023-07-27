#include "dice.h" 

int Dice::rollLoaded() {
    return 1;
}
int Dice::rollFair() {
    return 2;
}

int Dice::roll() {
    if(type == "load") {
        return rollLoaded();
    }
    return rollFair();
}


void Dice::setDice(std::string cmd) {
    type = cmd;
}


/*
 DiceType type = DiceType::LOADED;
 */