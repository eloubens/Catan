#include "dice.h" 
#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

int Dice::rollFair() {
    vector<int> d = {1, 2, 3, 4, 5, 6};
    int rollVal;
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng{seed};

    std::uniform_int_distribution<int> dist(0, d.size() - 1);

    int first = dist(rng);
    int second = dist(rng);

    int f = d[first];
    int s = d[second];

    rollVal = f + s;
    return rollVal;
}


void Dice::setDice(std::string cmd) {
    type = cmd;
}

string Dice::getDiceType() { return type; }

/*
 DiceType type = DiceType::LOADED;
 */