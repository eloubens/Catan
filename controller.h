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
    std::ostream &out = std::cout;
    std::istream &in = std::cin;
    std::ostream &err = std::cerr;
    Color turn = Color::B; // Blue goes first 
    std::unique_ptr<Model> model; // default ctor initializes to nullptr
    std::unique_ptr<View> view; // default ctor initializes to nullptr

    void roll(Color turn);
    void trade();
    // sets the Model field of the controller. Loads a board from a file, creates and loads a randomized board, or loads a saved game.
    void setModel(bool randomize, std::ostringstream &board_oss, unsigned &seed, vector<string> &arg_vec);
    // more functions
 public: 
    Controller(int argc, char * argv []);
    void general();
};



#endif