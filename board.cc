#include <iostream>
#include "board.h"
#include "tile.h"
#include "resourceEnum.h"
#include "tile.h"
#include "edgeEnum.h"
#include "vertexEnum.h"
 
using namespace std;

const int tilesNum = 19;

Board::Board(istringstream &iss, int geeseTileNum) : Board{iss, true} { 
    this->geeseTileNum = geeseTileNum; 
    tiles[geeseTileNum].setGeese();
}

Board::Board(istringstream &iss, bool isLoadGame): 
vertices{
    Vertex{"0"}, Vertex{"1"}, Vertex{"2"}, Vertex{"3"}, Vertex{"4"}, Vertex{"5"}, Vertex{"6"},
    Vertex{"7"}, Vertex{"8"}, Vertex{"9"}, Vertex{"10"}, Vertex{"11"}, Vertex{"12"}, Vertex{"13"},
    Vertex{"14"}, Vertex{"15"}, Vertex{"16"}, Vertex{"17"}, Vertex{"18"}, Vertex{"19"}, Vertex{"20"},
    Vertex{"21"}, Vertex{"22"}, Vertex{"23"}, Vertex{"24"}, Vertex{"25"}, Vertex{"26"}, Vertex{"27"},
    Vertex{"28"}, Vertex{"29"}, Vertex{"30"}, Vertex{"31"}, Vertex{"32"}, Vertex{"33"}, Vertex{"34"},
    Vertex{"35"}, Vertex{"36"}, Vertex{"37"}, Vertex{"38"}, Vertex{"39"}, Vertex{"40"}, Vertex{"41"},
    Vertex{"42"}, Vertex{"43"}, Vertex{"44"}, Vertex{"45"}, Vertex{"46"}, Vertex{"47"}, Vertex{"48"},
    Vertex{"49"}, Vertex{"50"}, Vertex{"51"}, Vertex{"52"}
},
edges{
    Edge{"0"}, Edge{"1"}, Edge{"2"}, Edge{"3"}, Edge{"4"}, Edge{"5"}, Edge{"6"},
    Edge{"7"}, Edge{"8"}, Edge{"9"}, Edge{"10"}, Edge{"11"}, Edge{"12"}, Edge{"13"},
    Edge{"14"}, Edge{"15"}, Edge{"16"}, Edge{"17"}, Edge{"18"}, Edge{"19"}, Edge{"20"},
    Edge{"21"}, Edge{"22"}, Edge{"23"}, Edge{"24"}, Edge{"25"}, Edge{"26"}, Edge{"27"},
    Edge{"28"}, Edge{"29"}, Edge{"30"}, Edge{"31"}, Edge{"32"}, Edge{"33"}, Edge{"34"},
    Edge{"35"}, Edge{"36"}, Edge{"37"}, Edge{"38"}, Edge{"39"}, Edge{"40"}, Edge{"41"},
    Edge{"42"}, Edge{"43"}, Edge{"44"}, Edge{"45"}, Edge{"46"}, Edge{"47"}, Edge{"48"},
    Edge{"49"}, Edge{"50"}, Edge{"51"}, Edge{"52"}, Edge{"53"}, Edge{"54"}, Edge{"55"},
    Edge{"56"}, Edge{"57"}, Edge{"58"}, Edge{"59"}, Edge{"60"}, Edge{"61"}, Edge{"62"},
    Edge{"63"}, Edge{"64"}, Edge{"65"}, Edge{"66"}, Edge{"67"}, Edge{"68"}, Edge{"69"}
},
tiles{
    Tile(0, &vertices[0], &vertices[1], &vertices[3], &vertices[4], &vertices[8], &vertices[9], &edges[0], &edges[1], &edges[3], &edges[4], &edges[8], &edges[9]),
    Tile(1, &vertices[2], &vertices[3], &vertices[7], &vertices[8], &vertices[13], &vertices[14], &edges[3], &edges[5], &edges[6], &edges[13], &edges[14], &edges[18]),
    Tile(2, &vertices[4], &vertices[5], &vertices[9], &vertices[10], &vertices[15], &vertices[16], &edges[4], &edges[7], &edges[8], &edges[15], &edges[16], &edges[19]),
    Tile(3, &vertices[6], &vertices[7], &vertices[12], &vertices[13], &vertices[18], &vertices[19], &edges[9], &edges[12], &edges[13], &edges[20], &edges[21], &edges[26]),
    Tile(4, &vertices[8], &vertices[9], &vertices[14], &vertices[15], &vertices[20], &vertices[21], &edges[10], &edges[14], &edges[15], &edges[22], &edges[23], &edges[27]),
    Tile(5, &vertices[10], &vertices[11], &vertices[16], &vertices[17], &vertices[22], &vertices[23], &edges[11], &edges[16], &edges[17], &edges[24], &edges[25], &edges[28]),
    Tile(6, &vertices[13], &vertices[14], &vertices[19], &vertices[20], &vertices[25], &vertices[26], &edges[18], &edges[21], &edges[22], &edges[30], &edges[31], &edges[35]),
    Tile(7, &vertices[15], &vertices[16], &vertices[21], &vertices[22], &vertices[27], &vertices[28], &edges[19], &edges[23], &edges[24], &edges[32], &edges[33], &edges[36]),
    Tile(8, &vertices[18], &vertices[19], &vertices[24], &vertices[25], &vertices[30], &vertices[31], &edges[26], &edges[29], &edges[30], &edges[37], &edges[38], &edges[43]),
    Tile(9, &vertices[20], &vertices[21], &vertices[26], &vertices[27], &vertices[32], &vertices[33], &edges[27], &edges[31], &edges[32], &edges[29], &edges[40], &edges[44]),
    Tile(10, &vertices[22], &vertices[23], &vertices[28], &vertices[29], &vertices[34], &vertices[35], &edges[28], &edges[33], &edges[34], &edges[41], &edges[42], &edges[45]),
    Tile(11, &vertices[25], &vertices[26], &vertices[31], &vertices[32], &vertices[37], &vertices[38], &edges[35], &edges[38], &edges[39], &edges[47], &edges[48], &edges[52]),
    Tile(12, &vertices[27], &vertices[28], &vertices[33], &vertices[34], &vertices[39], &vertices[40], &edges[36], &edges[40], &edges[41], &edges[49], &edges[50], &edges[53]),
    Tile(13, &vertices[30], &vertices[31], &vertices[36], &vertices[37], &vertices[42], &vertices[43], &edges[43], &edges[46], &edges[47], &edges[54], &edges[55], &edges[60]),
    Tile(14, &vertices[32], &vertices[33], &vertices[38], &vertices[39], &vertices[44], &vertices[45], &edges[44], &edges[48], &edges[49], &edges[56], &edges[57], &edges[61]),
    Tile(15, &vertices[34], &vertices[35], &vertices[40], &vertices[41], &vertices[46], &vertices[47], &edges[45], &edges[50], &edges[51], &edges[58], &edges[59], &edges[62]),
    Tile(16, &vertices[37], &vertices[38], &vertices[43], &vertices[44], &vertices[48], &vertices[49], &edges[52], &edges[55], &edges[56], &edges[63], &edges[64], &edges[67]),
    Tile(17, &vertices[39], &vertices[40], &vertices[45], &vertices[46], &vertices[50], &vertices[51], &edges[53], &edges[57], &edges[58], &edges[65], &edges[66], &edges[68]),
    Tile(18, &vertices[44], &vertices[45], &vertices[49], &vertices[50], &vertices[52], &vertices[53], &edges[61], &edges[64], &edges[65], &edges[69], &edges[70], &edges[71])
} {
    // reading in resources and tile values from ifs
    int tileVal, resoc;
    for (int i = 0 ; i < tilesNum; i++) {
        iss >> resoc >> tileVal;
        tiles[i].setTileVal(tileVal);
        if (isLoadGame) { 
            tiles[i].setResoc(static_cast<Resource>(resoc));
        } else if (tiles[i].setResocSetGeese(static_cast<Resource>(resoc))) { // isLoadGame = false here
            geeseTileNum = i;
        } 
    }

    // This is for 1 vertex in 1 tile
    // In tile 0, vertex Top left having adjacent vertices at Top Right and Middle Left
    tiles[0].placeAdjVerticesV(vertexEnum::TL, 
        vector<Vertex*>{tiles[0].getVertexAdr(vertexEnum::TR), tiles[0].getVertexAdr(vertexEnum::ML)});
    // In tile 0, vertex Top left having adjacent edges at Top and Top Left
    tiles[0].placeAdjEdgesV(vertexEnum::TL, 
        vector<Edge*>{tiles[0].getEdgeAdr(edgeEnum::T), tiles[0].getEdgeAdr(edgeEnum::TL)});

    // This is for 1 edge in 1 tile
    // In tile 0, edge Top having adjacent vertices at Top Left and Top Right
    tiles[0].placeAdjVerticesE(edgeEnum::T,
        vector<Vertex*>{tiles[0].getVertexAdr(vertexEnum::TL), tiles[0].getVertexAdr(vertexEnum::TR)});
    // In tile 0, edge Top having adjacent edges at Top Left and Top Right
    tiles[0].placeAdjEdgesE(edgeEnum::T,
        vector<Edge*>{tiles[0].getEdgeAdr(edgeEnum::TL), tiles[0].getEdgeAdr(edgeEnum::TR)});


}
    /*
    int tileVal, r;
    ifs >> r >> tileVal;
    tile[0].setVal(tileVal);
    tile[0].setResoc(r);   
   
    tile[0].placeAdjVerticesV(0, vector<Vertex*> temp {tile[0].getVertexAt(1), tile[0].getVertexAt(3)});
    placeAdjEdgesV

    Vertex Class:
    placeAdjVerticesV
    placeAdjEdgesV

    Edge Class:
    placeAdjVerticesE
    placeAdjEdgesE
*/

// returns tileNum that road is on
int Board::placeValidRoad(string edgeNum, Color color) {
    // finding what tile the road is on and placing it
    for (int i = 0; i < tilesNum; i++) {
        if(tiles[i].isPlaceValidRoad(edgeNum, color)) {
            return i;
        }
    }
    return -1; // just so compiler doesn't give a warning for no return statement
}

int Board::placeValidRes(string vertexNum, Color color, Residence res) {
     // finding what tile the res is on and placing it
    for (int i = 0; i < tilesNum; i++) {
        if(tiles[i].isPlaceValidRes(vertexNum, color, res)) {
            return i;
        }
    }
    return -1; // just so compiler doesn't give a warning for no return statement
}


pair<Resource, int> Board::getResoc(int tileNum, int tileValRolled, Color player) const {
    return tiles[tileNum].evalResoc(tileValRolled, player);
}