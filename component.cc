#include "component.h"
#include "colorEnum.h"
#include <sstream>
#include <utility>
#include <iostream>

using namespace std;
 
Component::Component(string location) : location{location} {}

Edge::Edge(string location) : Component{location} {}

Vertex::Vertex(string location) : Component{location} {}

string Edge::getEdge() {
    if (isRoad) {
        string s = getColorChar(player) + "R";
        return s; 
    } else {
        return location; 
    }
}

string Vertex::getVertex() {
    if (residenceType == Residence::NONE) {
        return location; 
    } else {
        ostringstream oss;
        oss << getColorChar(player); 
        oss << getResStr(residenceType);
        return oss.str();
    }
}

int Vertex::getResidenceAmount(Color color) const {
    if (player != color) return 0;
    return static_cast<int>(residenceType);
}

void Vertex::placeNonBasement(string vertexNum, Color c) {
    if (location != vertexNum) { return; }
    if (player != c || residenceType == Residence::NONE || residenceType == Residence::T) {
        throw pair<Residence, bool>{residenceType, false}; // meaning no residence was improved
    }
    residenceType = static_cast<Residence>(static_cast<int>(residenceType) + 1);
    throw pair<Residence, bool>{residenceType, true};
}

void Edge::placeRoad(string edgeNum, Color c) {
    if (location != edgeNum) { return; } // correct edge
    if (isRoad) { 
        throw false;
    } 
    for (auto v : adjVertices) {
        if (v->isOwnedBy(c)) {
            player = c;
            isRoad = true;
            throw true;
        }
    }
    for (auto e : adjEdges) {
        if (e->isOwnedBy(c)) {
            for (auto v : adjVertices) {
                if (e->hasAdjVertex(v)) {
                    if (!v->isOccupied()) {
                        player = c;
                        isRoad = true;
                        throw true;
                    }
                } 
            }
        }
    }
    throw false;
}

bool Edge::hasAdjVertex(Vertex *v) {
    for (auto adjV : adjVertices) {
        if (adjV == v) { return true; }
    }
    return false;
}

void Vertex::placeBasement(string bVertex, Color c, bool isDuringTurn) {
    if (location != bVertex) { return; }
    if (player != Color::DNE) { 
        throw false;
    }
    for (auto v : adjVertices) {
        if (v->isOccupied()) {
            throw false;
        }
    }
    if (isDuringTurn) {
        bool ownsAdjE = false;
        for (auto e : adjEdges) {
            if (e->isOwnedBy(c)) {
                ownsAdjE = true;
                break;
            }
        }
        if (ownsAdjE == false) { throw false; }
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
