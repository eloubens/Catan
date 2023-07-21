#ifndef RESIDENCE_H
#define RESIDENCE_H

// corresponding int represents number of resources gained by owning each residence
enum class Residence {
    NONE = 0, // no building poinst if residence doesn't exist
    B = 1, // basement
    H = 2, // house 
    T = 3 // tower
};

#endif