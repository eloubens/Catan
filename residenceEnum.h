#ifndef RESIDENCE_H
#define RESIDENCE_H
#include <string>

// the corresponding int represents the number of resources 
// gained by owning each residence
enum class Residence {
    NONE = 0, // no building poinst if residence doesn't exist
    B = 1, // basement
    H = 2, // house 
    T = 3 // tower
};

std::string getResStr(Residence r);
Residence getResFromStr(std::string r);

#endif
