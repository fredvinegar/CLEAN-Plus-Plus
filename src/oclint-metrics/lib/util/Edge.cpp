#include "oclint/util/Edge.h"

Edge :: Edge(Vertex *firstVertex, Vertex *secondVertex){
    this->firstVertex = firstVertex;
    this->secondVertex = secondVertex;
    (this->edge).push_back(firstVertex);
    (this->edge).push_back(secondVertex);
}
bool Edge :: containVertex(Vertex *vertex){
    if (*((this->edge).front()) == *vertex || *((this->edge).back()) == *vertex){
        return true;
    }
    return false;
}

Vertex* Edge ::  getOtherVertex(Vertex *vertex){
    if (*((this->edge).front()) == *vertex){
        return ((this->edge).back());
    }else if (*((this->edge).back()) == *vertex){
        return ((this->edge).front());
    }else{
        return NULL;
    }
}