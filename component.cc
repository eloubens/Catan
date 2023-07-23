#include "component.h"

using namespace std;
 
Component::Component(string location) : location{location} {}

//Component::Component(string location, Color playerType) : location{location}, playerType{playerType} {}

Edge::Edge(string location) : Component{location} {}
Vertex::Vertex(string location) : Component{location} {}


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