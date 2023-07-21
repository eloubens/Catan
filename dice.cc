#include "dice.h" 

int Dice::rollLoaded() {
    return 1;
}
int Dice::rollFair() {
    return 2;
}

int Dice::roll() {
    if(type == DiceType::LOADED) {
        return rollLoaded();
    }
    return rollFair();
}


/*
 DiceType type = DiceType::LOADED;
 */