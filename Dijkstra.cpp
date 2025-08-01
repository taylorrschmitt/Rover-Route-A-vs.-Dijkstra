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
    set<int> encountered;
    encountered.insert(root);
    set<int> notYet;

    for(auto it = graph.begin(); it != graph.end(); it++){
        if(root != it->first){
            notYet.insert(it->first);
        }
    }

    while(!notYet.empty()){

    }
}

int updateDistance(int to, int from, unordered_map<int, vector<pair<int,float>>> graph){
    for(auto it = graph.begin(); it != graph.end(); it++){
        if(it->first == to){
            
        }
    }
}