#include "component.h"
#include "colorEnum.h"
#include <sstream>
#include <iostream>

using namespace std;
 
Component::Component(string location) : location{location} {}

//Component::Component(string location, Color playerType) : location{location}, playerType{playerType} {}

Edge::Edge(string location) : Component{location} {}
Vertex::Vertex(string location) : Component{location} {}

string Edge::getEdge() {
    if (isRoad) {
        string s = getColorChar(player);
        return s; 
        // ostringstream oss;
        // if (player == Color::R) {oss << "R";}
        // else if (player == Color::B) {oss << "B";}
        // else if (player == Color::O) {oss << "O";}
        //else {oss << "Y";}
        //return oss.str(); 
    } else {
        return location; 
    }
}

string Vertex::getVertex() {
    if (residenceType == Residence::NONE) {
        return location; 
    } else {
        ostringstream oss;
        // if (player == Color::R) {oss << "R";}
        // else if (player == Color::B) {oss << "B";}
        // else if (player == Color::O) {oss << "O";}
        // else {oss << "Y";}
        // if (residenceType == Residence::H) {oss << "H";}
        // else if (residenceType == Residence::B) {oss << "B";}
        // else if (residenceType == Residence::T) {oss << "T";}
        oss << getColorChar(player); 
        oss << getResStr(residenceType);
        return oss.str();
    }
}

int Vertex::getResidenceAmount(Color color) const {
    if (player != color) return 0;
    return static_cast<int>(residenceType);



}

// void Vertex::findGetRes(string vertexNum) {
//     throw {residenceType, player};
// }

// throws Residence
void Vertex::placeNonBasement(string vertexNum, Color c) {
    if (location != vertexNum) { return; }
    if (player != c || residenceType == Residence::NONE || residenceType == Residence::T) {
        throw Residence::NONE; // meaning no residence was improved
    }
    residenceType = static_cast<Residence>(static_cast<int>(residenceType) + 1);
    throw residenceType;
}

// throws true or false
void Vertex::placeBasement(string bVertex, Color c, bool isDuringTurn) {
    if (location != bVertex) { return; } // correct vertex
    if (player != Color::DNE) { 
       // cout << "herwwwwwwe" << endl;
        throw false;
    } // check that it is totally empty

    for (auto v : adjVertices) {
        if (v->isOccupied()) {
            throw false;
        }
    }
    if (isDuringTurn) {
        bool ownsAdjEdge = false;
        for (auto e : adjEdges) {
            if (e->isOwnedBy(c)) {
                ownsAdjEdge = true;
                break;
            }
        }
        if (ownsAdjEdge == false) { throw false; }
    }
    player = c;
    residenceType = Residence::B;
    throw true;
}

bool Component::isOccupied() {
    if (player != Color::DNE) { return true; }
    return false;
}

bool Component::isOwnedBy(Color color) {
    return player == color;
}

string Component::getLocation() { return location; }

string Component::getPlayer() { return getColorChar(player); }

Residence Vertex::getRes() { return residenceType; }

bool Component::isPlayer(Color c) { return c == player; }

void Component::setAdjV(vector<Vertex*> &&adjVertices) {
    this->adjVertices = adjVertices;
}

void Component::setAdjE(std::vector<Edge*> &&adjEdges) {
    this->adjEdges = adjEdges;
}

bool Component::isNum(std::string num) { return location == num; }



void Edge::setValidRoad(Color color) { 
    isRoad = true; 
    player = color;
}

void Vertex::setValidRes(Color color, Residence res) {
    residenceType = res;
    player = color;
}
/*
Component:

int location
Color player
std::vector<Vertex*> adjVertices
std::vector<Edge*> adjEdges
*/

/*
Residence residenceType = Residence::NONE
*/

/*
bool isRoad = false;
*/