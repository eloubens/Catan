#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <map>
#include <memory>
#include <fstream>
#include <sstream>
#include "colorEnum.h"
#include "model.h"
#include "view.h"

extern const int invalidInput; // 1
extern const int eof; // 2
extern const int gameWon; // 3
extern const int tilesAmount; // 19
extern const int vertexMax; // 53
extern const int edgeMax; // 70

class Controller {
    std::ostream &out = std::cout;
    std::istream &in = std::cin;
    std::ostream &err = std::cerr;
    //int state = 0; // program state
    Color turn = Color::B; // Blue goes first 
    std::unique_ptr<Model> model; // default ctor initializes to nullptr
    std::unique_ptr<View> view; // default ctor initializes to nullptr

    int roll(Color turn);
    int trade();
    int geese();
    // sets the Model field of the controller. Loads a board from a file, creates and loads a randomized board, or loads a saved game.
    int setModel(bool canRandomize, bool foundRandomize, unsigned &seed, std::vector<string> &arg_vec);
    bool isSpecialState(int n);
    int save(std::string fileName = "backup.sv");
    int beginningOfGame();
    bool isEOF();
    int buildBasements(int i, bool isInc);
    // NEED TO ADD CODE HERE TO PRINT THE STATUS OF THE PLAYER IN FUNCTIONS LATER
    int beginningOfTurn(); 
    int DuringTurn();
    int buildRes(std::string vertexNum);
    int improveRes(std::string vertexNum);
    int buildRoad(std::string edgeNum);
    bool hasWon();

 public: 
    // no ctor
    void getStatus(int i);
    int general(std::vector<string> &arg_vec);
    int createController(std::vector<string> &arg_vec); // reads in command line inputs, creates model and view
};

#endif
