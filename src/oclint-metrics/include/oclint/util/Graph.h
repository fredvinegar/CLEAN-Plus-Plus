#ifndef ROBOTICS_GRAPH_H
#define ROBOTICS_GRAPH_H
#include <iostream>
#include <fstream>
#include <map>
#include <list>
#include <regex>
#include <algorithm>
#include <utility>
#include "Vertex.h"
#include "Edge.h"
using namespace std;


class Graph{
private:
    list<Vertex*> vertices;
    map<Vertex*,list<Vertex*>> adjacencyList;
    map<Vertex*,list<Vertex*>> directedAdjacencyList;
    map<Vertex*,list<Vertex*>> reversedDirectedAdjacencyList;
    map<Vertex*,bool> visitedVertices;
    list<list<Vertex*>> connectedComponents;
    map<Vertex*,list<Vertex*>> connectedComponentsMapping;
    list<list<Vertex*>> StronglyConnectedComponents;
    map<Vertex*,list<Vertex*>> StronglyConnectedComponentsMapping;
    list<Vertex*> helperVertexList;
    enum GraphAlingment{
        UNDIRECTED, DIRECTED, REVERSE_DIRECTED
    };
    void initializeEdge(Edge *edge);
    void initializeVertex(Vertex *vertex);
    void addDirectedEdge(Edge *edge);
    void addReverseDirectedEdge(Edge *edge);
    void addUndirectedEdge(Edge *edge);
    list<Vertex*> getAdjacentVertices(Vertex *vertex, GraphAlingment align);
public:

    void computeConnectedComponents();
    void computeStronglyConnectedComponents();
    void reversePassDFS();
    void straightPassDFS();
    void initializeVisitedVertices();
    void updateMapping(map<Vertex*, list<Vertex*>> *mapping, list<Vertex*> component);
    void depthFirstSearch(list<Vertex*> *connectedComponent, Vertex *vertex, Graph::GraphAlingment align);
    void addVertex(Vertex *vertex);
    void addEdge(Edge *edge);
    list<list<Vertex*>> getConnectedComponents();
    list<list<Vertex*>> getStronglyConnectedComponents();
    list<Vertex*> getComponentOfVertex(Vertex *vertex);
    list<Vertex*> getStrongComponentOfVertex(Vertex *vertex);
    bool inSameConnectedComponent(Vertex *vertex1, Vertex *vertex2);
    list<Vertex*> getAllVertices();

};




#endif //ROBOTICS_GRAPH_H
