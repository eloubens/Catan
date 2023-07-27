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
