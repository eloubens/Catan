#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <map>
#include <memory>
#include <fstream>
#include <sstream>
#include "colorEnum.h"
#include "model.h"
#include "view.h"
 
class Controller {
    Color turn = Color::B; // Blue goes first 
    std::unique_ptr<Model> model; // default ctor initializes to nullptr
    std::unique_ptr<View> view; // default ctor initializes to nullptr
    // add argv, argc, std::cout, std::cin

    void roll(Color turn);
    void trade();
    void generateRandomBoard();// change up

    // more functions
 public: 
    Controller();
    void general();
};



#endif