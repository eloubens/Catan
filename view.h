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
    string getResource(int n);
    void update(string & text, int &width, int &pad, int &right_pad, int &left_pad);
    void printTileTop(int prevPad, string v1, string v2, string e);
    void printBar(int prevPad);
    void printGeese(int prevPad);
    void printTileNum(int prevPad, string e1, string e2, int i);
    void printTileResoc(string text, int prevPad, int i) ;
    void printTileVal(string text, int prevPad, int i);
    void printVertex(string i);
    void printEdge(int prevPad, string i);
    void printSingleBar(int prevPad);
    void printBoard(); 
};

#endif
