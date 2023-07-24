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
    //int state = 0; // program state
    Color turn = Color::B; // Blue goes first 
    std::unique_ptr<Model> model; // default ctor initializes to nullptr
    std::unique_ptr<View> view; // default ctor initializes to nullptr

    void roll(Color turn);
    void trade();
    // sets the Model field of the controller. Loads a board from a file, creates and loads a randomized board, or loads a saved game.
    int setModel(bool canRandomize, bool foundRandomize, unsigned &seed, std::vector<string> &arg_vec);
    bool isBadState(int n);
 public: 
    // no ctor
    int general(std::vector<string> &arg_vec);
    int createController(std::vector<string> &arg_vec); // reads in command line inputs, creates model and view
};

#endif