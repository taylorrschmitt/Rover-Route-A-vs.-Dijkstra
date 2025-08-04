//
// Created by Evan Schroeder on 8/1/25.
//
#include "Dijkstra.h"

Dijkstra::Dijkstra(int rows, int cols, terrain& terrain) {
    float BigBigNum = 100000000.0;
    vertexNum = rows * cols;

    predecessors = new int[vertexNum];
    distances = new float[vertexNum];

    for(int i = 0; i < vertexNum; i++){
        predecessors[i] = -1;
        distances[i] = BigBigNum;
    }

    this->adjacencyList = terrain.getAdjacencyList();
    this->mapper = terrain.getMapper();
    this->reverseMapper = terrain.getReverseMapper();
}

Dijkstra::~Dijkstra() {
    delete[] predecessors;
    delete[] distances;
}

void Dijkstra::algorithm(int root) {
    set<int> visited;
    visited.insert(root);
    set<int> notVisited;

    //filling up the not visited set for the first iteration, updating distance of all vertices adjacent to root
    for(auto it = adjacencyList.begin(); it != adjacencyList.end(); it++){
        if(root != it->first){
            notVisited.insert(it->first);
        }
        if(updateDistance(root, it->first) != 0){
            distances[it->first] = updateDistance(root, it->first);
            predecessors[it->first] = root;
        }
    }
    while(!notVisited.empty()){
        //Finding u with smallest distance from root
        float smallestDist = 10000000.0;
        int u;
        for(auto it = notVisited.begin(); it != notVisited.end(); it++){
            if(distances[*it] < smallestDist){
                u = *it;
            }
        }
        notVisited.erase(u);
        visited.insert(u);

        //Relaxing all of the vertices adjacent to U
        vector<pair<int,float>> adjacentVertices = adjacencyList[u];
        for(int i = 0; i < adjacentVertices.size(); i++){
            if(notVisited.find(adjacentVertices.at(i).first) != notVisited.end()){
                if(distances[u] + adjacentVertices.at(i).second < distances[adjacentVertices.at(i).first]){
                    distances[adjacentVertices.at(i).first] = distances[u] + adjacentVertices.at(i).second;
                    predecessors[adjacentVertices.at(i).first] = u;
                }
            }
        }
    }
}

float Dijkstra::updateDistance(int to, int from){

    //Helper function for algorithm
    for(auto it = adjacencyList.begin(); it != adjacencyList.end(); it++){
        if(it->first == from){
            for(int i = 0; i < it->second.size(); i++){
                if(it->second.at(i).first == to){
                    return it->second.at(i).second;
                }
            }
        }
    }
    return 0;
}

vector<pair<int,int>> Dijkstra::getShortestPath(string from, string to){
    stringstream fromStream(from);
    int xFrom, yFrom, xTo, yTo;
    char dummy;

    fromStream >> dummy >> xFrom >> dummy >> yFrom >> dummy;
    pair<int, int> fromCoords(xFrom,yFrom);

    cout << "[" << xFrom << "," << yFrom << "]" <<endl;

    stringstream toStream(to);
    toStream >> dummy >> xTo >> dummy >> yTo >> dummy;
    pair<int, int> toCoords(xTo,yTo);

    cout << "[" << xTo << "," << yTo << "]" <<endl;
    return getShortestPathHelper(reverseMapper[fromCoords], reverseMapper[toCoords]);
}

vector<pair<int,int>> Dijkstra::getShortestPathHelper(int root, int destination) {
    algorithm(root);
    stack<pair<int,int>> pathStack;
    vector<pair<int,int>> path;

    //go through predecessors to find path and place on stack
    int currVertex = destination;
    while(currVertex != root){
        pathStack.push(mapper[currVertex]);
        currVertex = predecessors[currVertex];
    }

    //reverse stack onto a vector
    while(!pathStack.empty()){
        path.push_back(pathStack.top());
        pathStack.pop();
    }
    return path;
}

float Dijkstra::getShortestDistance(std::string from, std::string to) {
    stringstream fromStream(from);
    int xFrom, yFrom, xTo, yTo;
    char dummy;

    fromStream >> dummy >> xFrom >> dummy >> yFrom >> dummy;
    pair<int, int> fromCoords(xFrom,yFrom);

    stringstream toStream(to);
    toStream >> dummy >> xTo >> dummy >> yTo >> dummy;
    pair<int, int> toCoords(xTo,yTo);

    return getShortestDistanceHelper(reverseMapper[fromCoords], reverseMapper[toCoords]);
}
float Dijkstra::getShortestDistanceHelper(int root, int destination){
    algorithm(root);

    //iterate through path and add up the distance until you find root
    float distance = 0.0;
    int currVertex = destination;
    while(currVertex != root){
        distance += distances[currVertex];
        currVertex = predecessors[currVertex];
    }
    return distance;
}