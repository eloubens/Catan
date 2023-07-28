#include "colorEnum.h"

std::string getColorStr(Color c) {
    switch (c) {
        case Color::B:
            return "Blue";
        case Color::R:
            return "Red";
        case Color::O:
            return "Orange";
        default:
            return "Yellow";
    }
}

std::string getColorChar(Color c) {
    switch (c) {
        case Color::B:
            return "B";
        case Color::R:
            return "R";
        case Color::O:
            return "O";
        case Color::Y:
            return "Y";
        default:
            return "N";
    }
}