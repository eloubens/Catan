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
            return "WIFI";
        case Resource::PARK:
            return "PARK";
        default:
            return "NA";
    }
}

std::string getResocLowerCaseStr(Resource r) {
    switch (r) {
        case Resource::BRICK:
            return "brick";
        case Resource::ENERGY:
            return "energy";
        case Resource::GLASS:
            return "glass";
        case Resource::HEAT:
            return "heat";
        case Resource::WIFI:
            return "WiFi";
        case Resource::PARK:
            return "park";
        default:
            return "NA";
    }
}

Resource getResocR(std::string r) {
    if (r == "BRICK") return Resource::BRICK;
    else if (r == "ENERGY") return Resource::ENERGY;
    else if (r == "GLASS") return Resource::GLASS;
    else if (r == "HEAT") return Resource::HEAT;
    else if (r == "PARK") return Resource::PARK;
    else if (r == "WIFI") return Resource::WIFI;
    else return Resource::NA;
}


