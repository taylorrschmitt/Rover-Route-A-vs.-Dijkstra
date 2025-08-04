//
// Created by Evan Schroeder on 8/1/25.
//
#include<vector>
#include<utility>
#include<unordered_map>
#include<map>
#include<set>
#include<stack>
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
    ~Dijkstra();

    //Actual Dijkstra's algorithm and helper functions
    void algorithm(int root, unordered_map<int, vector<pair<int,float>>> graph);
    float updateDistance(int to, int from, unordered_map<int, vector<pair<int,float>>> graph);

    //functions that will be used in main to output
    float getShortestDistance(int root, int destination, unordered_map<int, vector<pair<int,float>>> graph);
    vector<pair<int,int>>getShortestPath(int root, int destination, unordered_map<int, vector<pair<int,float>>> graph,map<int, pair<int,int>> Mapper);
};


#endif //PATHFINDING_PERFORMANCE_ANALYSIS_DIJKSTRA_H
