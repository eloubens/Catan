#include "colorEnum.h"

std::string getColorStr(Color c) {
    switch (c) {
        case Color::B:
            return "B";
        case Color::R:
            return "R";
        case Color::O:
            return "O";
        default:
            return "Y";
    }
}
