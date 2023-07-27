#include "residenceEnum.h"

std::string getResStr(Residence r) {
    switch (r) {
        case Residence::B:
            return "B";
        case Residence::H:
            return "H";
        default:
            return "T";
    }
}