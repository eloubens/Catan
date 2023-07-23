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
    int argc; 
    char **argv; 
    std::ostream &out = std::cout;
    std::istream &in = std::cin;
    Color turn = Color::B; // Blue goes first 
    std::unique_ptr<Model> model; // default ctor initializes to nullptr
    std::unique_ptr<View> view; // default ctor initializes to nullptr

    void roll(Color turn);
    void trade();
    void generateRandomBoard();// change up

    // more functions
 public: 
    Controller(int argc, char * argv []);
    void general();
};



#endif