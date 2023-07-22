#ifndef RESOURCEENUM_H
#define RESOURCEENUM_H
 
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

#endif