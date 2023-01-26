#ifndef ROBOTICS_EDGE_H
#define ROBOTICS_EDGE_H
#include <iostream>
#include "Vertex.h"
#include <list>

using namespace std;

class Edge{
private:
    Vertex* firstVertex;
    Vertex* secondVertex;
    list<Vertex*> edge;
public:
    Edge(Vertex *firstVertex, Vertex *secondVertex);
    Vertex* getFirstVertex(){
        return this->firstVertex;
    };
    Vertex* getSecondVertex(){
        return this->secondVertex;
    };
    list<Vertex*> getVertices(){
        return this->edge;
    };
    bool containVertex(Vertex *vertex);
    Vertex* getOtherVertex(Vertex *vertex);
};
#endif //ROBOTICS_EDGE_H
