#include "component.h"
#include <sstream>
#include <iostream>

using namespace std;
 
Component::Component(string location) : location{location} {}

//Component::Component(string location, Color playerType) : location{location}, playerType{playerType} {}

Edge::Edge(string location) : Component{location} {}
Vertex::Vertex(string location) : Component{location} {}

string Edge::getEdge() {
    if (isRoad) {
        ostringstream oss;
        if (player == Color::R) {oss << "R";}
        else if (player == Color::B) {oss << "B";}
        else if (player == Color::O) {oss << "O";}
        else {oss << "Y";}
        return oss.str();
    } else {
        return location; 
    }
}

string Vertex::getVertex() {
    if (residenceType == Residence::NONE) {
        return location; 
    } else {
        ostringstream oss;
        if (player == Color::R) {oss << "R";}
        else if (player == Color::B) {oss << "B";}
        else if (player == Color::O) {oss << "O";}
        else {oss << "Y";}
        
        if (residenceType == Residence::H) {oss << "H";}
        else if (residenceType == Residence::B) {oss << "B";}
        else if (residenceType == Residence::T) {oss << "T";}

        return oss.str();
    }
}

int Vertex::getResidenceAmount(Color color) const {
    if (player != color) return 0;
    return static_cast<int>(residenceType);
}

void Component::setAdjV(vector<Vertex*> &&adjVertices) {
    this->adjVertices = adjVertices;
}

void Component::setAdjE(std::vector<Edge*> &&adjEdges) {
    this->adjEdges = adjEdges;
}

bool Component::isNum(std::string num) { return this->location == location; }



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