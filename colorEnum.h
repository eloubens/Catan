#ifndef COLORENUM_H
#define COLORENUM_H
#include <string>
 
const int playerAmount = 4;

// corresponding integer represents players spot in the array in the Controller class
enum class Color {
    B = 0, // Player 1, Blue
    R = 1, // Player 2, Red
    O = 2, // Player 3, Orange
    Y = 3,  // Player 4, Yellow
    DNE = -1
};

std::string getColorStr(Color c);

std::string getColorChar(Color c);

#endif
