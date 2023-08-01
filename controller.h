#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <map>
#include <memory>
#include <fstream>
#include <sstream>
#include "colorEnum.h"
#include "model.h"
#include "view.h"
#include "board.h"

extern const int invalidInput; // 1
extern const int eof; // 2
extern const int gameWon; // 3
extern const int vertexMax; // 53
extern const int edgeMax; // 70

class Controller {
    bool wasBoardLoad = false;
    std::ostream &out = std::cout;
    std::istream &in = std::cin;
    std::ostream &err = std::cerr;

    Color turn = Color::B; // Blue goes first 
    std::unique_ptr<Model> model; 
    std::unique_ptr<View> view;

    int roll(Color turn);
    int trade();
    int geese();
    int setModel(bool canRandomize, bool foundRandomize, unsigned &seed, std::vector<string> &arg_vec);
    // sets the Model field of the controller. Either loads a board from a file, creates and loads a randomized board, or loads a saved game.
    
    bool isSpecialState(int n);
    int save(std::string fileName = "backup.sv");
    int beginningOfGame();
    bool isEOF();
    int buildDefaultBasements(int i, bool isInc);
    int beginningOfTurn(); 
    int DuringTurn();
    void buildRes(std::string vertexNum);
    void improveRes(std::string vertexNum);
    void buildRoad(std::string edgeNum);
    bool hasWon();
    void printHelp();
    void printStatus(int i);
    void printResidences();
    void reset();
    void randomize(std::ostringstream& board_oss, unsigned& seed);
 public: 
    // no ctor
    int general(std::vector<string> &arg_vec);
    int createController(std::vector<string> &arg_vec); // reads command line inputs, creates model and view
};

#endif
