#ifndef COMPONENT_H
#define COMPONENT_H
#include <vector>
#include <string>
#include "residenceEnum.h"
#include "colorEnum.h"

class Edge;
class Vertex;
 
class Component {   
    std::string location; //vertex number or edge number
 protected:
    Color playerType = Color::DNE; //Player that built res/road
    std::vector<Vertex*> adjVertices;
    std::vector<Edge*> adjEdges;
 
    bool isOwnedBy(Color color) const;
    bool isOccupied() const;
    bool hasAdjVertices() const;
    bool hasAdjEdges() const;
 public:
    explicit Component(std::string location);
    Component(std::string location,  Color playerType);
    // virtual void print() const = 0;

    void setAdjV(std::vector<Vertex*> &&adjVertices);
    void setAdjE(std::vector<Edge*> &&adjEdges);
};


class Edge final : public Component {
    bool isRoad = false;
 public:
    Edge(std::string location);
    // void print() const override;
    void checkRoad(Color color, int edge) const; // ???
};




class Vertex final : public Component {
    Residence residenceType = Residence::NONE;
 public: 
  Vertex(std::string location);
    int getResidenceAmount(Color color) const;
    void printResidences() const;
    //void print() const override;

};

#endif