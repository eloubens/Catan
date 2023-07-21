#ifndef RESOURCEENUM_H
#define RESOURCEENUM_H
 
// types of resources
enum class Resource {
    BRICK,
    ENERGY,
    GLASS,
    HEAT,
    WIFI,
    PARK, 
    NA // not applicable, acts like null for pointers
};

#endif