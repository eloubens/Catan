#include "component.h"

using namespace std;
 
Component::Component(int location) : location{location} {}
Component::Component(int location,  Color playerType) : location{location}, playerType{playerType} {}
Edge::Edge(int location) : Component{location} {}
Vertex::Vertex(int location) : Component{location} {}


int Vertex::getResidenceAmount(Color color) const {
    if (playerType != color) return 0;
    return static_cast<int>(residenceType);

}

/*
Component:

int location
Color playerType
std::vector<Vertex*> adjVertices
std::vector<Edge*> adjEdges
*/

/*
Residence residenceType = Residence::NONE
*/

/*
bool isRoad = false;
*/