#include "residenceEnum.h"

std::string getResStr(Residence r) {
    switch (r) {
        case Residence::B:
            return "B";
        case Residence::H:
            return "H";
        case Residence::T:
            return "T";
        default:
            return "NONE";
    }
}

Residence getResFromStr(std::string s) {
    if (s == "B") {
        return Residence::B;
    } else if (s == "H") {
        return Residence::H;
    } else if (s == "T"){
        return Residence::T;
    } else {
        return Residence::NONE;
    }
}
