#ifndef ROBOTICS_VERTEX_H
#define ROBOTICS_VERTEX_H
#include <iostream>
using namespace std;

enum VerType {Method, Field, Record};
class Vertex{
private:
    string name;
    VerType type;
public:
    Vertex(string name, VerType type);
    bool operator==(Vertex &vertex);
    bool operator==(const Vertex &vertex);
    bool isSameVertex(string name, VerType type);
    VerType getType();
    string getName();

};
#endif //ROBOTICS_VERTEX_H
