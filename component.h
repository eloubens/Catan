#ifndef COMPONENT_H
#define COMPONENT_H
#include <vector>
#include "residenceEnum.h"
#include "colorEnum.h"

class Edge;
class Vertex;

class Component {
   int location; //vertex number or edge number
   Color playerType = Color::DNE; // Doesn't get initialized if empty!! //Player that built res/road
   std::vector<Vertex*> adjVertices;
   std::vector<Edge*> adjEdges;
 protected:
   bool isOwnedBy(Color color) const;
   bool isOccupied() const;
   bool hasAdjVertices() const;
   bool hasAdjEdges() const;
 public:
   Component(int location);
   // virtual void print() const = 0;
};



class Edge final : public Component {
   bool isRoad = false;
 public:
   Edge(int location);
   // void print() const override;
   void checkRoad(Color color, int edge) const;
};




class Vertex final : public Component {
   Residence residenceType = Residence::NONE;
 public: 
   Vertex(int location);
   int getResidenceAmount(Color color) const;
   void printResidences() const;
   //void print() const override;

};

#endif