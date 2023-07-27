 #include "resourceEnum.h"

std::string getResocStr(Resource r) {
    switch (r) {
        case Resource::BRICK:
            return "BRICK";
        case Resource::ENERGY:
            return "ENERGY";
        case Resource::GLASS:
            return "GLASS";
        case Resource::HEAT:
            return "HEAT";
        case Resource::WIFI:
            return "HEAT";
        case Resource::PARK:
            return "PARK";
        default:
            return "NA";
    }
}