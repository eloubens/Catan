#include "component.h"

using namespace std;

Component::Component(int location) : location{location} {}
Edge::Edge(int location) : Component{location} {}
Vertex::Vertex(int location) : Component{location} {}