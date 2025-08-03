//
// Created by Evan Schroeder on 8/1/25.
//

#include "Dijkstra.h"

Dijkstra::Dijkstra(int rows, int cols) {
    float BigBigNum = 100000000.0;
    vertexNum = rows * cols;

    for(int i = 0; i < vertexNum; i++){
        predecessors[i] = -1;
        distances[i] = BigBigNum;
    }

}

Dijkstra::~Dijkstra() {
    delete[] predecessors;
    delete[] distances;
}

void Dijkstra::algorithm(int root, unordered_map<int, vector<pair<int,float>>> graph) {
    set<int> visited;
    visited.insert(root);
    set<int> notVisited;

    for(auto it = graph.begin(); it != graph.end(); it++){
        if(root != it->first){
            notVisited.insert(it->first);
        }
        if(updateDistance(root, it->first, graph) != 0){
            distances[it->first] = updateDistance(root, it->first, graph);
            predecessors[it->first] = root;
        }
    }
    while(!notVisited.empty()){
        int smallestDist = 10000000;
        int u;
        for(auto it = notVisited.begin(); it != notVisited.end(); it++){
            if(distances[*it] < smallestDist){
                u = *it;
            }
        }
        notVisited.erase(u);
        visited.insert(u);
        vector<pair<int,float>> adjacentVertices = graph[u];
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

float Dijkstra::updateDistance(int to, int from, unordered_map<int, vector<pair<int,float>>> graph){
    for(auto it = graph.begin(); it != graph.end(); it++){
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

vector<pair<int,int>> Dijkstra::getShortestPath(int root, int destination, unordered_map<int, vector<pair<int,float>>> graph, map<int, pair<int,int>> mapper) {
    algorithm(root,graph);
    stack<pair<int,int>> pathStack;
    vector<pair<int,int>> path;

    int currVertex = destination;
    while(currVertex != root){
        pathStack.push(mapper[currVertex]);
        currVertex = predecessors[currVertex];
    }

    while(!pathStack.empty()){
        path.push_back(pathStack.top());
        pathStack.pop();
    }
    return path;
}

float Dijkstra::getShortestDistance(int root, int destination, unordered_map<int, vector<pair<int,float>>> graph){
    algorithm(root, graph);

    float distance = 0.0;
    int currVertex = destination;
    while(currVertex != root){
        distance += distances[currVertex];
        currVertex = predecessors[currVertex];
    }
    return distance;
}