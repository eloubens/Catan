#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <map>
#include "colorEnum.h"
#include "model.h"


 
class Controller {
    Color turn = Color::B; // Blue goes first 
    Model model;

    void roll();
    void trade();
    void generateRandomBoard();// change up

    // more functions
 public: 
    // Controller();
    void general();
};



#endif