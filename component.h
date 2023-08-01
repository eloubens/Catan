#ifndef COMPONENT_H
#define COMPONENT_H
#include <vector>
#include <string>
#include "residenceEnum.h"
#include "colorEnum.h"

using namespace std; 

class Edge;
class Vertex;
 
class Component {   
 protected:
 	string location; // vertex number or edge number
	Color player = Color::DNE; // Player that built res/road
	vector<Vertex*> adjVertices;
	vector<Edge*> adjEdges;
 public:
 	explicit Component(string location);
 	bool isOccupied();
 	bool isOwnedBy(Color color);
	void setAdjV(vector<Vertex*> &&adjVertices);
	void setAdjE(vector<Edge*> &&adjEdges);
	bool isNum(string num); // returns true if location matches the location of the vertex/edge
	bool isPlayer(Color c);
	string getLocation();
	string getPlayer();
};

class Edge final : public Component {
	bool isRoad = false;
	bool hasAdjVertex(Vertex *v);
 public:
 	void placeRoad(string edgeNum, Color c);
	explicit Edge(string location); // ctor
	void setValidRoad(Color color); // places a road, known to be valid
	string getEdge();
};

class Vertex final : public Component {
	Residence residenceType = Residence::NONE;
 public: 
	explicit Vertex(string location);
	void placeNonBasement(string vertexNum, Color c);
	int getResidenceAmount(Color color) const; // returns the corresponding num for a residence only if its owned by color
	void setValidRes(Color color, Residence res);
	Residence getRes();
	/* throws true if vertex found and basement was placed.
        throws false if vertex found and basement can't be placed.
        doesn't do anything if vertex not found. */
	void placeBasement(string bVertex, Color c, bool isDuringTurn);
	string getVertex(); 
};

#endif
