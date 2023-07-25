#include <iostream>
#include <iomanip>
#include "view.h"
#include "model.h"

using namespace std;

View::View(Model *model) : model{model} {}

void View::printt() {
    cout << "hadeya" << endl; 
    //model->board.printBoard(); 
}


const int textPad = 2; 
const int fillPad = 8; 

string View::getResource(int n) {
    if (n == 0) { return "BRICK";}
    if (n == 1) { return "ENERGY";}
    if (n == 2) { return "GLASS";}
    if (n == 3) { return "HEAT";}
    if (n == 4) { return "WIFI";}
    else { return "PARK";}
}


void View::update(string & text, int &width, int &pad, int &right_pad, int &left_pad) {
    pad = (width - text.length()) / 2;
    right_pad = pad;
    left_pad = width - text.length() - right_pad;
}

void View::printTileTop(int prevPad, string v1, string v2, string e) {
    cout << setw(prevPad) << "|" << setw(textPad) << v1 << "|" << "--" << setw(textPad) << e <<  "--" << "|" << setw(textPad) << v2 << "|"; 
}

void View::printBar(int prevPad) {
    cout << setw(prevPad) << "|" << setw(10) << "|"; 
}

void View::printTileNum(int prevPad, string e1, string e2, int i) {
    string text = to_string(i); 
    int width = 8;
    int pad = (width - text.length()) / 2;
    int leftPad = pad;
    int rightPad = width - text.length() - leftPad;
    cout << setw(prevPad + textPad) << e1 << setw(rightPad) << "" << text << setw(leftPad) << "" << setw(textPad)<< e2; 
}

//void Board::printTileResoc(const std::vector<Tile>& tileResource, int prevPad, int i) {
void View::printTileResoc(string text, int prevPad, int i) {    
    //string text = tileResource[i].resocType; 
    int width = 9;
    int pad = (width - text.length()) / 2;
    int leftPad = pad;
    int rightPad = width - text.length() - leftPad;
    cout << setw(prevPad) << "|" << setw(rightPad) << "" << text << setw(leftPad) << "" << "|";
}

//void Board::printTileVal(const std::vector<Tile>& tileVec, int prevPad, int i) {
void View::printTileVal(string text, int prevPad, int i) {
    //string text = to_string(tileVec[i].tileValue); 
    int width = 6;
    int pad = (width - text.length()) / 2;
    int leftPad = pad;
    int rightPad = width - text.length() - leftPad;
    cout << setw(rightPad) << "" << text << setw(leftPad) << ""; 
}

void View::printVertex(string i) {
    cout << "|" << setw(textPad) << i << "|"; 
}

void View::printEdge(int prevPad, string i) {
    cout << setw(textPad + prevPad + 1) << i ; 
}

void View::printSingleBar(int prevPad) {
    cout << setw(prevPad + textPad + 1) << "|"; 
}



void View::printBoard() {
    string text; 
    int textPad = 2; 
    int spacePad = 21;

    Tile * tiles = model->board.tiles; 
    int i = 0;
    //printTileTop(spacePad + 1, "0", "0", "1");  
    printTileTop(spacePad + 1, tiles[i].getVertexTL(), tiles[i].getVertexTR(), tiles[i].getEdgeT());  
    
    cout << endl;  

    // printing 1 tile
    printBar(spacePad + textPad); 
    cout << endl; 
    printTileNum(spacePad, tiles[i].getEdgeTL(), tiles[i].getEdgeTR(), i);
    cout << endl; 
    printTileResoc(tiles[i].getResource(), spacePad + textPad, i); 
    cout << endl; 

    // printing 2 tiles 
    spacePad -= 10;  
    printTileTop(spacePad + 1, tiles[i + 1].getVertexTL(), tiles[i + 1].getVertexTL(), tiles[i + 1].getEdgeT()); 
    printTileVal(tiles[i].getTileValue(), 0, i);
    printTileTop(0, tiles[i + 2].getVertexTL(), tiles[i + 2].getVertexTL(), tiles[i + 2].getEdgeT()); 
    cout << endl;
    i++;
    printBar(spacePad + textPad); 
    printBar(spacePad - textPad + 1); 
    cout << endl; 
    printTileNum(spacePad, tiles[i].getEdgeTL(), tiles[i].getEdgeTR(), i);
    printTileNum(fillPad,  tiles[i + 1].getEdgeTL(), tiles[i + 1].getEdgeTR(), i + 1);
    cout << endl; 
    printTileResoc(tiles[i].getResource(), spacePad + textPad, i);
    printTileResoc(tiles[i + 1].getResource(), fillPad + textPad, i + 1);
    cout << endl; 
    spacePad -= 10;
    // i = 1
    printTileTop(spacePad + 1, tiles[i + 2].getVertexTL(), tiles[i + 2].getVertexTL(), tiles[i + 2].getEdgeT());
    printTileVal(tiles[i].getTileValue(), 0, i);
    printTileTop(spacePad , tiles[i + 3].getVertexTL(), tiles[i + 3].getVertexTL(), tiles[i + 3].getEdgeT()); 
    printTileVal(tiles[i].getTileValue(), 0, i + 1);
    printTileTop(spacePad , tiles[i + 4].getVertexTL(), tiles[i + 4].getVertexTL(), tiles[i + 4].getEdgeT()); 
    cout << endl; 
    printBar(spacePad + textPad);
    printBar(spacePad + fillPad + 1); 
    printBar(spacePad + fillPad  + 1); 
    cout << endl;
    i += 2; 
    // i = 3
    //printTileNum(spacePad, "12", "13", i );
    printTileNum(spacePad, tiles[i].getEdgeTL(), tiles[i].getEdgeTR(), i);
    //printTileNum(spacePad + fillPad, "14", "15", i + 1);
    printTileNum(spacePad + fillPad, tiles[i + 1].getEdgeTL(), tiles[i + 1].getEdgeTR(), i + 1);
    //printTileNum(spacePad + fillPad - 1, "16", "17", i + 2);
    printTileNum(spacePad + fillPad - 1, tiles[i + 2].getEdgeTL(), tiles[i + 2].getEdgeTR(), i + 2);
    cout << endl;
    printTileResoc(tiles[i].getResource(), spacePad + textPad, i);
    printTileResoc(tiles[i + 1].getResource(), fillPad + textPad, i + 1);
    printTileResoc(tiles[i + 2].getResource(), fillPad + textPad, i + 2);
    cout << endl; 
    //printVertex("12");
    printVertex(tiles[i].getEdgeTL());
    printTileVal(tiles[i].getTileValue(), 0, i);
    //printTileTop(0, "13", "14", "18"); 
    printTileTop(0, tiles[i + 3].getVertexTR(), tiles[i + 3].getVertexTL(), tiles[i + 3].getEdgeT()); 
    printTileVal(tiles[i].getTileValue(), 0, i + 1);
    //printTileTop(textPad, "15", "16", "19"); 
    printTileTop(0, tiles[i + 4].getVertexTR(), tiles[i + 4].getVertexTL(), tiles[i + 4].getEdgeT());  
    printTileVal(tiles[i].getTileValue(), 0, i + 2);
    //printVertex("17");
    printVertex(tiles[i + 1].getEdgeTL());
    cout << endl; 
    printBar(spacePad + textPad);
    printBar(spacePad + fillPad + 1); 
    printBar(spacePad + fillPad  + 1); 
    cout << endl; 
    i += 3; 
    // i = 6;
    //printEdge(0, "20");
    printEdge(0, tiles[i - 3].getEdgeBL());

    //printTileNum(spacePad + fillPad, "21", "22", i );
    printTileNum(spacePad + fillPad, tiles[i].getEdgeTL(), tiles[i].getEdgeTR(), i);
    //printTileNum(spacePad + fillPad - 1, "23", "24", i + 1);
    printTileNum(spacePad + fillPad, tiles[i + 1].getEdgeTL(), tiles[i + 1].getEdgeTR(), i + 1);
    
    //printEdge(fillPad - 1, "25");    
    printEdge(0, tiles[i - 2].getEdgeBL());
    cout << endl; 
    
    printSingleBar(0); 
    
    printTileResoc(tiles[i].getResource(), fillPad + textPad, i);
    printTileResoc(tiles[i + 1].getResource(), fillPad + textPad, i + 1);
    printSingleBar(fillPad - 1); 
    cout << endl; 
    
    //printTileTop(spacePad + 1, "18", "19", "26");  
    printTileTop(spacePad + 1, tiles[i - 3].getVertexBL(), tiles[i - 3].getVertexBR(), tiles[i - 3].getEdgeB());  
    printTileVal(tiles[i].getTileValue(), 0, i);
    //printTileTop(spacePad, "20", "21", "27"); 
    printTileTop(spacePad, tiles[i - 2].getVertexBL(), tiles[i - 2].getVertexBR(), tiles[i - 2].getEdgeB());  
    printTileVal(tiles[i].getTileValue(), 0, i + 1);
    
    //printTileTop(spacePad, "22", "23", "28"); 
    printTileTop(spacePad, tiles[i - 1].getVertexBL(), tiles[i - 1].getVertexBR(), tiles[i - 1].getEdgeB());  
    cout << endl; 
    printBar(spacePad + textPad);
    printBar(spacePad + fillPad + 1); 
    printBar(spacePad + fillPad  + 1); 
    cout << endl; 
    i += 2; 

    // i = 8 
    //printTileNum(spacePad, "29", "30", i );
    printTileNum(spacePad, tiles[i].getEdgeTL(), tiles[i].getEdgeTR(), i);
    //printTileNum(spacePad +  fillPad , "31", "32", i + 1);
    printTileNum(spacePad +  fillPad, tiles[i + 1].getEdgeTL(), tiles[i + 1].getEdgeTR(), i + 1);

    // printTileNum(spacePad +  fillPad - 1, "33", "34", i + 2);
    printTileNum(spacePad +  fillPad - 1, tiles[i + 2].getEdgeTL(), tiles[i + 2].getEdgeTR(), i + 2);
    cout << endl; 
    printTileResoc(tiles[i].getResource(), spacePad + textPad, i);
    printTileResoc(tiles[i + 1].getResource(), fillPad + textPad, i + 1);
    printTileResoc(tiles[i + 2].getResource(), fillPad + textPad, i + 2);
    cout << endl; 

    //printVertex("24");
    printVertex(tiles[i].getVertexML());
    
    printTileVal(tiles[i].getTileValue(), 0, i);

    //printTileTop(0, "25", "26", "35"); 
    printTileTop(0, tiles[i + 3].getVertexTL(), tiles[i + 3].getVertexTR(), tiles[i + 3].getEdgeT()); 
    
    printTileVal(tiles[i].getTileValue(), 0, i + 1);

    // printTileTop(textPad, "27", "28", "35"); 
    printTileTop(0, tiles[i + 3].getVertexTL(), tiles[i + 4].getVertexTR(), tiles[i + 4].getEdgeT()); 
    printTileVal(tiles[i].getTileValue(), 0, i + 2);
    
    // printVertex("29");
    printVertex(tiles[i + 2].getVertexMR());

    cout << endl; 
    
    printBar(spacePad + textPad);
    printBar(spacePad + fillPad + 1); 
    printBar(spacePad + fillPad  + 1); 
    cout << endl; 
    i += 3; 
    // i = 11

    //printEdge(0, "37");
    printEdge(0, tiles[i - 3].getEdgeBL());

    //printTileNum(spacePad + fillPad, "38", "39", i );
    printTileNum(spacePad + fillPad, tiles[i].getEdgeTL(), tiles[i].getEdgeTR(), i );
    
    //printTileNum(spacePad + fillPad - 1, "40", "41", i + 1);
    printTileNum(spacePad + fillPad - 1, tiles[i + 1].getEdgeTL(), tiles[i + 1].getEdgeTR(), i + 1);

    // printEdge(fillPad - 1, "42"); 
    printEdge(fillPad - 1, tiles[i - 1].getEdgeBR());
    cout << endl; 

    printSingleBar(0); 
    printTileResoc(tiles[i].getResource(), fillPad + textPad, i);
    printTileResoc(tiles[i + 1].getResource(), fillPad + textPad, i + 1);
    printSingleBar(fillPad - 1); 
    cout << endl; 

    printTileTop(spacePad + 1, tiles[i + 2].getVertexTL(), tiles[i + 2].getVertexTL(), tiles[i + 2].getEdgeT());  
    printTileVal(tiles[i].getTileValue(), 0, i);
    //printTileTop(spacePad, "32", "33", "44"); 
    printTileTop(spacePad + 1, tiles[i + 3].getVertexTL(), tiles[i + 3].getVertexTL(), tiles[i + 3].getEdgeT());  
    printTileVal(tiles[i].getTileValue(), 0, i + 1);
    printTileTop(spacePad + 1, tiles[i + 4].getVertexTL(), tiles[i + 4].getVertexTL(), tiles[i + 4].getEdgeT());  
    //printTileTop(spacePad, "34", "35", "45"); 
    
    cout << endl; 
    printBar(spacePad + textPad);
    printBar(spacePad + fillPad + 1); 
    printBar(spacePad + fillPad  + 1); 
    cout << endl; 
    i += 2; 
    // i = 13
    //printTileNum(spacePad,"46", "47", i );
    printTileNum(spacePad, tiles[i].getEdgeTL(), tiles[i].getEdgeTR(), i );

    //printTileNum(spacePad +  fillPad , "48", "49", i + 1);
    printTileNum(spacePad + fillPad, tiles[i + 1].getEdgeTL(), tiles[i + 1].getEdgeTR(), i + 1);

    //printTileNum(spacePad +  fillPad - 1, "50", "51", i + 2);
    printTileNum(spacePad + fillPad - 1, tiles[i + 2].getEdgeTL(), tiles[i + 2].getEdgeTR(), i + 2);    
    cout << endl; 

    printTileResoc(tiles[i].getResource(), spacePad + textPad, i);
    printTileResoc(tiles[i + 1].getResource(), fillPad + textPad, i + 1);
    printTileResoc(tiles[i + 2].getResource(), fillPad + textPad, i + 2);
    cout << endl; 


    //printVertex("36");
    printVertex(tiles[i].getVertexBL());
    
    printTileVal(tiles[i].getTileValue(), 0, i);
    //printTileTop(0, "37", "38", "52");
    printTileTop(0, tiles[i - 2].getVertexBL(), tiles[i - 2].getVertexBR(), tiles[i - 2].getEdgeB());

    printTileVal(tiles[i].getTileValue(), 0, i + 1);
    
    //printTileTop(textPad, "39", "40", "53"); 
    printTileTop(0, tiles[i - 1].getVertexBL(), tiles[i - 1].getVertexBR(), tiles[i - 1].getEdgeB());
    
    printTileVal(tiles[i].getTileValue(), 0, i + 2);
    // printVertex("41");
    printVertex(tiles[i + 1].getVertexBR());
    cout << endl;

    printBar(spacePad + textPad);
    printBar(spacePad + fillPad + 1); 
    printBar(spacePad + fillPad  + 1); 
    cout << endl; 
    i += 3; 
    
    // i = 15
    //printEdge(0, "54");
    printEdge(0, tiles[i - 2].getEdgeBL());
    //printTileNum(spacePad + fillPad, "55", "56", i );
    printTileNum(spacePad + fillPad, tiles[i + 1].getEdgeTL(), tiles[i + 1].getEdgeTL(), i );
    //printTileNum(spacePad + fillPad - 1, "57", "58", i + 1);
    printTileNum(spacePad + fillPad - 1, tiles[i + 2].getEdgeTL(), tiles[i + 2].getEdgeTL(), i + 1);
    //printEdge(fillPad - 1, "59");
    printEdge(fillPad - 1, tiles[i].getEdgeBR());
    
    cout << endl; 
    printSingleBar(0); 
    printTileResoc(tiles[i].getResource(), fillPad + textPad, i);
    printTileResoc(tiles[i + 1].getResource(), fillPad + textPad, i + 1);
    printSingleBar(fillPad - 1); 

    cout << endl; 
   // printTileTop(spacePad + 1, "42", "43", "60");  
    printTileTop(spacePad + 1, tiles[i - 2].getVertexBL(), tiles[i - 2].getVertexBR(), tiles[i - 2].getEdgeB());
    printTileVal(tiles[i].getTileValue(), 0, i);
    //printTileTop(spacePad, "44", "45", "61"); 
    printTileTop(spacePad,  tiles[i - 1].getVertexBL(), tiles[i - 1].getVertexBR(), tiles[i - 1].getEdgeB()); 
    printTileVal(tiles[i].getTileValue(), 0, i + 1);
    // printTileTop(spacePad, "46", "47", "62"); 
    printTileTop(spacePad,  tiles[i].getVertexBL(), tiles[i].getVertexBR(), tiles[i].getEdgeB()); 
    cout << endl;

    spacePad += 10; 
    i++;
    // i = 16 
    printBar(spacePad + textPad); 
    printBar(spacePad - textPad + 1); 
    i++; 
    // i = 17 
    cout << endl; 
    // printEdge(spacePad , "63");
    printEdge(spacePad, tiles[i - 2].getEdgeBL());
    //printTileNum(fillPad, "64", "65", i);
    printTileNum(fillPad, tiles[i + 1].getEdgeTR(), tiles[i + 1].getEdgeTL(), i);
    //printEdge(fillPad - 1, "66");
    printEdge(fillPad - 1, tiles[i].getVertexBR());
    cout << endl; 
    printSingleBar(spacePad - 1);
    printTileResoc(tiles[i].getResource(), fillPad + textPad, i);
    printSingleBar(fillPad - 1);
    cout << endl; 
    //printTileTop(spacePad + 1, "48", "49", "67"); 
    printTileTop(spacePad + 1, tiles[i - 2].getVertexBL(), tiles[i - 2].getVertexBR(), tiles[i - 2].getEdgeB()); 
    printTileVal(tiles[i].getTileValue(), 0, i);
    //printTileTop(0, "50", "51", "68"); 
    printTileTop(0, tiles[i - 1].getVertexBL(), tiles[i - 1].getVertexBR(), tiles[i - 1].getEdgeB()); 
    spacePad += 10; 
    i++;
    // i = 18 
    cout << endl; 
    printBar(spacePad + textPad); 
    cout << endl; 
    //printEdge(spacePad, "69");
    printEdge(spacePad, tiles[i - 1].getEdgeBL());
    printEdge(fillPad - 1, tiles[i - 1].getEdgeBR());
    cout << endl; 
    printBar(spacePad + textPad); 
    cout << endl; 
    //printTileTop(spacePad + 1, "52", "53", "71"); 
    printTileTop(spacePad + 1, tiles[i - 1].getVertexBL(), tiles[i - 1].getVertexBR(), tiles[i - 1].getEdgeB()); 
    cout << endl; 
}


