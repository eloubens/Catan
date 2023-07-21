#ifndef COLORENUM_H
#define COLORENUM_H

// corresponding integer represents players spot in the array in the Controller class
enum class Color {
    B = 0, // Player 1
    R = 1, // Player 2
    O = 2, // Player 3
    Y = 3,  // Player 4
    DNE = -1 // player does not exist
};

#endif