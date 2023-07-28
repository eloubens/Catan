#include "dice.h" 
#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

int Dice::rollLoaded() {

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

string Dice::getDiceType() { return type; }

/*
 DiceType type = DiceType::LOADED;
 */