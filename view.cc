#include <iostream>
#include <iomanip>
#include "view.h"
#include "model.h"
#include "tile.h"

using namespace std;

View::View(Model *model) : model{model} {}

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

void View::printTileResoc(string text, int prevPad, int i) {  
    int width = 9;
    int pad = (width - text.length()) / 2;
    int leftPad = pad;
    int rightPad = width - text.length() - leftPad;
    cout << setw(prevPad) << "|" << setw(rightPad) << "" << text << setw(leftPad) << "" << "|";
}

void View::printTileVal(string text, int prevPad, int i) {
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

    Tile * tiles = model->board.getTile(); 
    int i = 0;

    // ROW 1:  | 0|-- 0--| 1| 
    printTileTop(spacePad + 1, tiles[i].getVertex(vertexEnum::TL), tiles[i].getVertex(vertexEnum::TR) , tiles[i].getEdge(edgeEnum::T));  cout << endl;  

    printBar(spacePad + textPad); cout << endl; 
    printTileNum(spacePad, tiles[i].getEdge(edgeEnum::TL), tiles[i].getEdge(edgeEnum::TR), i); cout << endl; 
    printTileResoc(tiles[i].getResource(), spacePad + textPad, i); cout << endl; 

    spacePad -= 10;  
    printTileTop(spacePad + 1, tiles[i + 1].getVertex(vertexEnum::TL) , tiles[i + 1].getVertex(vertexEnum::TR), tiles[i + 1].getEdge(edgeEnum::T)); 
    printTileVal(tiles[i].getTileValue(), 0, i);
    printTileTop(0, tiles[i + 2].getVertex(vertexEnum::TL) , tiles[i + 2].getVertex(vertexEnum::TR), tiles[i + 2].getEdge(edgeEnum::T)); 
    cout << endl;

    // ROW 2:  | 2|-- 3--| 3|   3  | 4|-- 4--| 5|

    i++; // i = 1
    printBar(spacePad + textPad); 
    printBar(spacePad - textPad + 1); cout << endl;

    printTileNum(spacePad, tiles[i].getEdge(edgeEnum::TL), tiles[i].getEdge(edgeEnum::TR), i);
    printTileNum(fillPad,  tiles[i + 1].getEdge(edgeEnum::TL), tiles[i + 1].getEdge(edgeEnum::TR), i + 1); cout << endl; 
    printTileResoc(tiles[i].getResource(), spacePad + textPad, i);
    printTileResoc(tiles[i + 1].getResource(), fillPad + textPad, i + 1); cout << endl; 
    spacePad -= 10;
    
    printTileTop(spacePad + 1, tiles[i + 2].getVertex(vertexEnum::TL) , tiles[i + 2].getVertex(vertexEnum::TR), tiles[i + 2].getEdge(edgeEnum::T));
    printTileVal(tiles[i].getTileValue(), 0, i);
    printTileTop(spacePad , tiles[i + 3].getVertex(vertexEnum::TL) , tiles[i + 3].getVertex(vertexEnum::TR), tiles[i + 3].getEdge(edgeEnum::T)); 
    printTileVal(tiles[i + 1].getTileValue(), 0, i + 1);
    printTileTop(spacePad , tiles[i + 4].getVertex(vertexEnum::TL) , tiles[i + 4].getVertex(vertexEnum::TR), tiles[i + 4].getEdge(edgeEnum::T));  cout << endl; 
    // ROW 3:  | 6|-- 9--| 7|  10  | 8|--10--| 9|  10  |10|--11--|11|

    printBar(spacePad + textPad);
    printBar(spacePad + fillPad + 1); 
    printBar(spacePad + fillPad  + 1); cout << endl;
    i += 2; // i = 3
    printTileNum(spacePad, tiles[i].getEdge(edgeEnum::TL), tiles[i].getEdge(edgeEnum::TR), i);
    printTileNum(spacePad + fillPad, tiles[i + 1].getEdge(edgeEnum::TL), tiles[i + 1].getEdge(edgeEnum::TR), i + 1);
    printTileNum(spacePad + fillPad - 1, tiles[i + 2].getEdge(edgeEnum::TL), tiles[i + 2].getEdge(edgeEnum::TR), i + 2);
    cout << endl;
    printTileResoc(tiles[i].getResource(), spacePad + textPad, i);
    printTileResoc(tiles[i + 1].getResource(), fillPad + textPad, i + 1);
    printTileResoc(tiles[i + 2].getResource(), fillPad + textPad, i + 2);
    cout << endl; 
    cout << " ";
    printVertex(tiles[i].getVertex(vertexEnum::ML));
    printTileVal(tiles[i].getTileValue(), 0, i);
    printTileTop(0, tiles[i + 3].getVertex(vertexEnum::TL) , tiles[i + 3].getVertex(vertexEnum::TR), tiles[i + 3].getEdge(edgeEnum::T)); 
    printTileVal(tiles[i + 1].getTileValue(), 0, i + 1);
    printTileTop(0, tiles[i + 4].getVertex(vertexEnum::TL) , tiles[i + 4].getVertex(vertexEnum::TR), tiles[i + 4].getEdge(edgeEnum::T));  
    printTileVal(tiles[i + 2].getTileValue(), 0, i + 2);
    printVertex(tiles[i + 2].getVertex(vertexEnum::MR));
    cout << endl; 
    // ROW 4:  |12|      |13|--18--|14|      |15|--19--|16|      |17|

    printBar(spacePad + textPad);
    printBar(spacePad + fillPad + 1); 
    printBar(spacePad + fillPad  + 1); 
    cout << endl; 
    i += 3; // i = 6;
    printEdge(0, tiles[i - 3].getEdge(edgeEnum::BL));
    printTileNum(spacePad + fillPad, tiles[i].getEdge(edgeEnum::TL), tiles[i].getEdge(edgeEnum::TR), i);
    printTileNum(spacePad + fillPad - 1, tiles[i + 1].getEdge(edgeEnum::TL), tiles[i + 1].getEdge(edgeEnum::TR), i + 1);
    printEdge(fillPad - 1, tiles[i - 1].getEdge(edgeEnum::BR)); cout << endl; 
    printSingleBar(0); 
    printTileResoc(tiles[i].getResource(), fillPad + textPad, i);
    printTileResoc(tiles[i + 1].getResource(), fillPad + textPad, i + 1);
    printSingleBar(fillPad - 1); cout << endl;
    printTileTop(spacePad + 1, tiles[i - 3].getVertex(vertexEnum::BL), tiles[i - 3].getVertex(vertexEnum::BR) , tiles[i - 3].getEdge(edgeEnum::B));  
    printTileVal(tiles[i].getTileValue(), 0, i);
    printTileTop(spacePad, tiles[i - 2].getVertex(vertexEnum::BL), tiles[i - 2].getVertex(vertexEnum::BR) , tiles[i - 2].getEdge(edgeEnum::B));  
    printTileVal(tiles[i + 1].getTileValue(), 0, i + 1);
    printTileTop(spacePad, tiles[i - 1].getVertex(vertexEnum::BL), tiles[i - 1].getVertex(vertexEnum::BR) , tiles[i - 1].getEdge(edgeEnum::B)); cout << endl; 
    // ROW 5:  |18|--26--|19|  11  |20|--27--|21|  11  |22|--28--|23|

    printBar(spacePad + textPad);
    printBar(spacePad + fillPad + 1); 
    printBar(spacePad + fillPad  + 1); cout << endl; 
    i += 2; // i = 8 

    printTileNum(spacePad, tiles[i].getEdge(edgeEnum::TL), tiles[i].getEdge(edgeEnum::TR), i);
    printTileNum(spacePad +  fillPad, tiles[i + 1].getEdge(edgeEnum::TL), tiles[i + 1].getEdge(edgeEnum::TR), i + 1);
    printTileNum(spacePad +  fillPad - 1, tiles[i + 2].getEdge(edgeEnum::TL), tiles[i + 2].getEdge(edgeEnum::TR), i + 2); cout << endl; 
    
    printTileResoc(tiles[i].getResource(), spacePad + textPad, i);
    printTileResoc(tiles[i + 1].getResource(), fillPad + textPad, i + 1);
    printTileResoc(tiles[i + 2].getResource(), fillPad + textPad, i + 2); cout << endl; 
    cout << " ";
    printVertex(tiles[i].getVertex(vertexEnum::ML) );
    printTileVal(tiles[i].getTileValue(), 0, i);
    printTileTop(0, tiles[i + 3].getVertex(vertexEnum::TL) , tiles[i + 3].getVertex(vertexEnum::TR), tiles[i + 3].getEdge(edgeEnum::T)); 
    printTileVal(tiles[i + 1].getTileValue(), 0, i + 1);
    printTileTop(0, tiles[i + 4].getVertex(vertexEnum::TL) , tiles[i + 4].getVertex(vertexEnum::TR), tiles[i + 4].getEdge(edgeEnum::T)); 
    printTileVal(tiles[i + 2].getTileValue(), 0, i + 2);
    printVertex(tiles[i + 2].getVertex(vertexEnum::MR)); cout << endl; 
    // ROW 6: |24|   8  |25|--35--|26|   8  |27|--36--|28|   8  |29|  

    printBar(spacePad + textPad);
    printBar(spacePad + fillPad + 1); 
    printBar(spacePad + fillPad  + 1); cout << endl; 
    i += 3; // i = 11
    printEdge(0, tiles[i - 3].getEdge(edgeEnum::BL));
    printTileNum(spacePad + fillPad, tiles[i].getEdge(edgeEnum::TL), tiles[i].getEdge(edgeEnum::TR), i );
    printTileNum(spacePad + fillPad - 1, tiles[i + 1].getEdge(edgeEnum::TL), tiles[i + 1].getEdge(edgeEnum::TR), i + 1);
    printEdge(fillPad - 1, tiles[i - 1].getEdge(edgeEnum::BR)); cout << endl; 
    printSingleBar(0); 
    printTileResoc(tiles[i].getResource(), fillPad + textPad, i);
    printTileResoc(tiles[i + 1].getResource(), fillPad + textPad, i + 1);
    printSingleBar(fillPad - 1); cout << endl; 
    printTileTop(spacePad, tiles[i + 2].getVertex(vertexEnum::TL) , tiles[i + 2].getVertex(vertexEnum::TR), tiles[i + 2].getEdge(edgeEnum::T));  
    printTileVal(tiles[i].getTileValue(), 0, i);
    printTileTop(spacePad + 1, tiles[i + 3].getVertex(vertexEnum::TL), tiles[i + 3].getVertex(vertexEnum::TR), tiles[i + 3].getEdge(edgeEnum::T));  
    printTileVal(tiles[i + 1].getTileValue(), 0, i + 1);
    printTileTop(spacePad - 1, tiles[i + 4].getVertex(vertexEnum::TL), tiles[i + 4].getVertex(vertexEnum::TR), tiles[i + 4].getEdge(edgeEnum::T));  cout << endl;
    // ROW 7: |30|--43--|31|   8   |32|--44--|33|   8  |34|--45--|35|

    printBar(spacePad + textPad);
    printBar(spacePad + fillPad + 1); 
    printBar(spacePad + fillPad  + 1); cout << endl; 
    i += 2; // i = 13
    printTileNum(spacePad, tiles[i].getEdge(edgeEnum::TL), tiles[i].getEdge(edgeEnum::TR), i );
    printTileNum(spacePad + fillPad, tiles[i + 1].getEdge(edgeEnum::TL), tiles[i + 1].getEdge(edgeEnum::TR), i + 1);
    printTileNum(spacePad + fillPad - 1, tiles[i + 2].getEdge(edgeEnum::TL), tiles[i + 2].getEdge(edgeEnum::TR), i + 2); cout << endl; 
    printTileResoc(tiles[i].getResource(), spacePad + textPad, i);
    printTileResoc(tiles[i + 1].getResource(), fillPad + textPad, i + 1);
    printTileResoc(tiles[i + 2].getResource(), fillPad + textPad, i + 2); cout << endl; 
    cout << " ";
    printVertex(tiles[i].getVertex(vertexEnum::ML) );
    printTileVal(tiles[i].getTileValue(), 0, i);
    printTileTop(0, tiles[i - 2].getVertex(vertexEnum::BL), tiles[i - 2].getVertex(vertexEnum::BR) , tiles[i - 2].getEdge(edgeEnum::B));
    printTileVal(tiles[i + 1].getTileValue(), 0, i + 1);
    printTileTop(0, tiles[i - 1].getVertex(vertexEnum::BL), tiles[i - 1].getVertex(vertexEnum::BR) , tiles[i - 1].getEdge(edgeEnum::B));
    printTileVal(tiles[i + 2].getTileValue(), 0, i + 2);
    printVertex(tiles[i + 2].getVertex(vertexEnum::MR)); cout << endl;
    // ROW 8:  |36|   5  |37|--52--|38|   5  |39|--53--|40|   5  |41|  

    printBar(spacePad + textPad);
    printBar(spacePad + fillPad + 1); 
    printBar(spacePad + fillPad  + 1); cout << endl; 
    i += 3; // i = 15

    printEdge(0, tiles[i - 3].getEdge(edgeEnum::BL));
    printTileNum(spacePad + fillPad, tiles[i].getEdge(edgeEnum::TL), tiles[i].getEdge(edgeEnum::TR), i );
    printTileNum(spacePad + fillPad - 1, tiles[i + 1].getEdge(edgeEnum::TL), tiles[i + 1].getEdge(edgeEnum::TR), i + 1);
    printEdge(fillPad - 1, tiles[i - 1].getEdge(edgeEnum::BR)); cout << endl; 
    printSingleBar(0); 
    printTileResoc(tiles[i].getResource(), fillPad + textPad, i);
    printTileResoc(tiles[i + 1].getResource(), fillPad + textPad, i + 1);
    printSingleBar(fillPad - 1); cout << endl;
     
    printTileTop(spacePad + 1, tiles[i - 3].getVertex(vertexEnum::BL), tiles[i - 3].getVertex(vertexEnum::BR) , tiles[i - 3].getEdge(edgeEnum::B));
    printTileVal(tiles[i].getTileValue(), 0, i);
    printTileTop(spacePad,  tiles[i - 2].getVertex(vertexEnum::BL), tiles[i - 2].getVertex(vertexEnum::BR) , tiles[i - 2].getEdge(edgeEnum::B)); 
    printTileVal(tiles[i + 1].getTileValue(), 0, i + 1);
    printTileTop(spacePad,  tiles[i - 1].getVertex(vertexEnum::BL), tiles[i - 1].getVertex(vertexEnum::BR) , tiles[i - 1].getEdge(edgeEnum::B)); cout << endl;
    // ROW 9: |42|--60--|43|   6  |44|--61--|45|   6  |46|--62--|47|

    spacePad += 10; 
    i+= 2; // i = 17
    printBar(spacePad + textPad); 
    printBar(spacePad - textPad + 1); cout << endl; 
    printEdge(spacePad, tiles[i - 2].getEdge(edgeEnum::BL));
    printTileNum(fillPad, tiles[i].getEdge(edgeEnum::TL), tiles[i].getEdge(edgeEnum::TR), i);
    printEdge(fillPad - 1, tiles[i - 1].getEdge(edgeEnum::BR)); cout << endl; 
    printSingleBar(spacePad - 1);
    printTileResoc(tiles[i].getResource(), fillPad + textPad, i);
    printSingleBar(fillPad - 1); cout << endl; 
    printTileTop(spacePad + 1, tiles[i - 2].getVertex(vertexEnum::BL), tiles[i - 2].getVertex(vertexEnum::BR) , tiles[i - 2].getEdge(edgeEnum::B)); 
    printTileVal(tiles[i].getTileValue(), 0, i);
    printTileTop(0, tiles[i - 1].getVertex(vertexEnum::BL), tiles[i - 1].getVertex(vertexEnum::BR) , tiles[i - 1].getEdge(edgeEnum::B)); cout << endl; 
    spacePad += 10; 
    i++; // i = 18
    // ROW 10: |48|--67--|49|   9  |50|--68--|51|

    printBar(spacePad + textPad); cout << endl; 
    printEdge(spacePad, tiles[i - 1].getEdge(edgeEnum::BL)); 
    printEdge(fillPad - 1, tiles[i - 1].getEdge(edgeEnum::BR)); cout << endl; 
    printBar(spacePad + textPad); cout << endl; 
    printTileTop(spacePad + 1, tiles[i - 1].getVertex(vertexEnum::BL), tiles[i - 1].getVertex(vertexEnum::BR) , tiles[i - 1].getEdge(edgeEnum::B)); 
    cout << endl; 
    // ROW 11: |52|--71--|53|
}