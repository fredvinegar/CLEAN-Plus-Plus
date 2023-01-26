#include "oclint/util/Graph.h"


bool getVisitedVerticesMapValue(map<Vertex*,bool> vertexBoolMap, Vertex *vertex){
    for (auto it = vertexBoolMap.begin(); it != vertexBoolMap.end(); it++){
        if (*vertex == *(it->first)){
            return it->second;
        }
    }
    return false;
}

bool isInVerticesList (list<Vertex*> verticesList, Vertex *vertex){
    for (auto it = verticesList.begin(); it != verticesList.end(); it++) {
        if(**it == *vertex){
            return true;
        }
    }
    return false;
}

list<Vertex*> getMapValue(map<Vertex*,list<Vertex*>> m, Vertex *vertex){
    for (auto it = m.begin(); it != m.end(); it++) {
        if (*vertex == *(it->first)) {
            return it->second;
        }
    }
    list<Vertex*> emptyList;
    return emptyList;
}

bool isInMapKeys(map<Vertex*,list<Vertex*>> map, Vertex *key){
    for (auto it = map.begin(); it != map.end(); it++) {
        if (*key == *(it->first)) {
            return true;
        }
    }
    return false;
}

void Graph :: computeConnectedComponents(){
    this->initializeVisitedVertices();
    for (auto vertex = (this->vertices).begin() ; vertex != (this->vertices).end() ; vertex++){
        if (!getVisitedVerticesMapValue(this->visitedVertices, *vertex)){
            list<Vertex*> connectedComponent;
            depthFirstSearch(&connectedComponent, *vertex, UNDIRECTED);
            (this->connectedComponents).push_back(connectedComponent);
            updateMapping(&(this->connectedComponentsMapping), connectedComponent);
        }
    }
}

void Graph :: initializeVisitedVertices(){
    for (auto vertex = (this->vertices).begin() ; vertex != (this->vertices).end() ; vertex++){
        if (this->visitedVertices.size() == 0 ){
            map<Vertex*,bool> newVisitedVertices;
            this->visitedVertices = newVisitedVertices;
        }
        (this->visitedVertices).insert({*vertex,false});
        }
}

void Graph :: updateMapping(map<Vertex*, list<Vertex*>> *mapping, list<Vertex*> component){
    for (auto comp = component.begin() ; comp != component.end() ; comp++){
        (*mapping).insert({*comp, component});
    }
}

void Graph :: depthFirstSearch(list<Vertex*> *connectedComponent, Vertex *vertex, Graph::GraphAlingment align){
    map<Vertex*,bool> :: iterator it = (this->visitedVertices).find(vertex);
    if (it != (this->visitedVertices).end()){
        it->second = true;
    }
    if (align != REVERSE_DIRECTED){
        connectedComponent->push_back(vertex);
    }
    list<Vertex*> adjacentVertices = getAdjacentVertices(vertex,align);
    for (auto adjacentVertex = adjacentVertices.begin() ; adjacentVertex != adjacentVertices.end() ; adjacentVertex++){
        if(!getVisitedVerticesMapValue(this->visitedVertices, *adjacentVertex)){
            depthFirstSearch(connectedComponent,*adjacentVertex,align);
        }
    }

    if (align == REVERSE_DIRECTED){
        (this->helperVertexList).push_back(vertex);
    }
}

void Graph :: addVertex(Vertex *vertex){
    if (!getVisitedVerticesMapValue(this->visitedVertices, vertex)){
        this->initializeVertex(vertex);
    }
}

void Graph :: addEdge(Edge *edge) {
    this->initializeEdge(edge);
    this->addDirectedEdge(edge);
    this->addUndirectedEdge(edge);
}

void Graph :: initializeEdge(Edge *edge){
    if(!isInMapKeys(this->adjacencyList,edge->getFirstVertex())){
        initializeVertex(edge->getFirstVertex());
    }
    if(!isInMapKeys(this->adjacencyList,edge->getSecondVertex())){
        initializeVertex(edge->getSecondVertex());
    }
}

void Graph :: initializeVertex(Vertex *vertex){
    if (! isInVerticesList(this->vertices, vertex)){
        list<Vertex*> newList1;
        list<Vertex*> newList2;
        list<Vertex*> newList3;
        (this->adjacencyList).insert({vertex, newList1});
        (this->directedAdjacencyList).insert({vertex, newList2});
        (this->reversedDirectedAdjacencyList).insert({vertex, newList3});
        (this->vertices).push_back(vertex);
    }
}

void Graph :: addDirectedEdge(Edge *edge){
    list<Vertex*> adjacentVertices = getMapValue((this->directedAdjacencyList),edge->getFirstVertex());
    if (!(find(adjacentVertices.begin(), adjacentVertices.end(), edge->getSecondVertex()) != adjacentVertices.end())){
        adjacentVertices.push_back(edge->getSecondVertex());
        map<Vertex*,list<Vertex*>> :: iterator it = (this->directedAdjacencyList).find(edge->getFirstVertex());
        if (it != (this->directedAdjacencyList).end()){
            it->second = adjacentVertices;
        }else {
            (this->directedAdjacencyList).insert({edge->getFirstVertex(),adjacentVertices});
        }
        this->addReverseDirectedEdge(edge);
    }
}

void Graph :: addReverseDirectedEdge(Edge *edge){
    list<Vertex*> adjacentVertices = getMapValue((this->reversedDirectedAdjacencyList),edge->getSecondVertex());
    adjacentVertices.push_back(edge->getFirstVertex());
    (this->reversedDirectedAdjacencyList).insert({edge->getSecondVertex(), adjacentVertices});
}

void Graph :: addUndirectedEdge(Edge *edge) {
    list <Vertex*> vertices = edge->getVertices();
    for (auto vertex = vertices.begin(); vertex != vertices.end(); vertex++) {
        list<Vertex*> adjacentVertices = getMapValue((this->adjacencyList),*vertex);
        if (!isInVerticesList(adjacentVertices, edge->getOtherVertex(*vertex))) {
            adjacentVertices.push_back(edge->getOtherVertex(*vertex));
            map<Vertex*,list<Vertex*>> :: iterator it = (this->adjacencyList).find(*vertex);
            if (it != (this->adjacencyList).end()){
                it->second = adjacentVertices;
            }else {
                (this->adjacencyList).insert({*vertex,adjacentVertices});
            }
        }
    }
}

list<Vertex*> Graph :: getAdjacentVertices(Vertex *vertex, Graph::GraphAlingment align){
    if (align == UNDIRECTED) {
        return getMapValue(this->adjacencyList,vertex);
    } else if (align == DIRECTED) {
        return getMapValue(this->directedAdjacencyList,vertex);
    } else if (align == REVERSE_DIRECTED) {
        return getMapValue(this->reversedDirectedAdjacencyList,vertex);
    }
    list<Vertex*> emptyList;
    return emptyList;
}


list<list<Vertex*>> Graph ::  getConnectedComponents() {
    return this->connectedComponents;
}

list<list<Vertex*>> Graph ::  getStronglyConnectedComponents() {
    return this->StronglyConnectedComponents;
}

list<Vertex*> Graph :: getComponentOfVertex(Vertex *vertex) {
    return getMapValue(this->connectedComponentsMapping,vertex);
}

list<Vertex*> Graph :: getStrongComponentOfVertex(Vertex *vertex) {
    return getMapValue(this->StronglyConnectedComponentsMapping,vertex);
}

bool Graph :: inSameConnectedComponent(Vertex *vertex1, Vertex *vertex2) {
    return getComponentOfVertex(vertex1) == (getComponentOfVertex(vertex2));
    // not sure if working. if not need to realy implement compare betaween two lists.
}

list<Vertex*> Graph :: getAllVertices(){
    return this->vertices;
}

void Graph :: reversePassDFS(){
    this->initializeVisitedVertices();
    for (auto vertex = (this->vertices).begin() ; vertex != (this->vertices).end() ; vertex++){
        if (!getVisitedVerticesMapValue(this->visitedVertices, *vertex)){
            list<Vertex*> stronglyConnectedComponent;
            depthFirstSearch(&stronglyConnectedComponent, *vertex, REVERSE_DIRECTED);
        }
    }
}
void Graph :: straightPassDFS(){
    this->initializeVisitedVertices();
    for (auto vertex = (this->helperVertexList).begin() ; vertex != (this->helperVertexList).end() ; vertex++){
        if (!getVisitedVerticesMapValue(this->visitedVertices, *vertex)){
            list<Vertex*> stronglyConnectedComponent;
            depthFirstSearch(&stronglyConnectedComponent, *vertex, DIRECTED);
            this->StronglyConnectedComponents.push_back(stronglyConnectedComponent);
            this->updateMapping(&(this->StronglyConnectedComponentsMapping),stronglyConnectedComponent);

        }
    }
}

void Graph :: computeStronglyConnectedComponents(){
    this->reversePassDFS();
    this->straightPassDFS();
}