//
// Created by Evan Schroeder on 8/1/25.
//
#include"terrain.h"
#include<vector>
#include<utility>
#include<unordered_map>
#include<map>
#include<set>
#include<stack>
#include<sstream>
#include<iostream>
using namespace std;

#ifndef PATHFINDING_PERFORMANCE_ANALYSIS_DIJKSTRA_H
#define PATHFINDING_PERFORMANCE_ANALYSIS_DIJKSTRA_H

class Dijkstra {
    float shortestPath;
    int vertexNum;
    int* predecessors;
    float* distances;

    unordered_map<int, vector<pair<int,float>>> adjacencyList;
    map<int, pair<int, int>> mapper;
    map<pair<int,int>, int> reverseMapper;
public:
    Dijkstra(int rows, int cols, terrain& terrain);
    ~Dijkstra();

    //Actual Dijkstra's algorithm and helper functions
    void algorithm(int root);
    float updateDistance(int to, int from);

    //functions that will be used in main to output
    float getShortestDistance(string from, string to);
    float getShortestDistanceHelper(int root, int destination);

    vector<pair<int,int>>getShortestPath(string from, string to);
    vector<pair<int,int>>getShortestPathHelper(int root, int destination);
};


#endif //PATHFINDING_PERFORMANCE_ANALYSIS_DIJKSTRA_H
