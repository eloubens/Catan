#ifndef VIEW_H
#define VIEW_H
#include <iostream>
#include <memory>
#include "model.h"

using namespace std;

class View {
    Model *model;

 public:
    View(Model *model);
    //printBoard(Model* model);
};

#endif