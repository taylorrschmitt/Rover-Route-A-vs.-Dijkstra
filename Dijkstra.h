//
// Created by Evan Schroeder on 8/1/25.
//
#include<vector>
#include<utility>
#include<unordered_map>
#include<set>
using namespace std;

#ifndef PATHFINDING_PERFORMANCE_ANALYSIS_DIJKSTRA_H
#define PATHFINDING_PERFORMANCE_ANALYSIS_DIJKSTRA_H


class Dijkstra {
    float shortestPath;
    int vertexNum;
    int* predecessors = new int[vertexNum];
    float* distances = new float[vertexNum];
public:
    Dijkstra(int rows, int cols);
    void algorithm(int root, unordered_map<int, vector<pair<int,float>>> graph);
    float getShortestDistance();
    vector<pair<int,int>>getShortestPath();
    bool updateDistance(int to, int from, unordered_map<int, vector<pair<int,float>>> graph);
    ~Dijkstra();
};


#endif //PATHFINDING_PERFORMANCE_ANALYSIS_DIJKSTRA_H
