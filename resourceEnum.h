#ifndef RESOURCEENUM_H
#define RESOURCEENUM_H
#include <string>

const int resocAmount = 6; 

// types of resources
enum class Resource {
    BRICK = 0,
    ENERGY = 1,
    GLASS = 2,
    HEAT = 3,
    WIFI = 4,
    PARK = 5,
    NA // not applicable, acts like null for pointers
};

std::string getResocStr(Resource r);

#endif