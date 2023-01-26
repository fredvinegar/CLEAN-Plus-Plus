#include "oclint/util/Vertex.h"

Vertex :: Vertex(string name, VerType type){
this->name = name;
this->type = type;
}
bool Vertex :: operator==(Vertex &vertex){
    if (this->name == vertex.name && this->type == vertex.type){
        return true;
    }
    return false;
}
bool Vertex :: operator==(const Vertex &vertex){
    if (this->name == vertex.name && this->type == vertex.type){
        return true;
    }
    return false;
}

bool Vertex :: isSameVertex(string name, VerType type){
    if (this->name == name && this->type == type){
        return true;
    }
    return false;
}

VerType Vertex :: getType(){
    return this->type;
}

string Vertex :: getName(){
    return this->name;
}
