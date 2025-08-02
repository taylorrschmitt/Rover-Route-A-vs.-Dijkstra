//
// Created by taylor on 8/1/2025.
//

#ifndef ASTAR_H
#define ASTAR_H
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include "terrain.h"
using namespace std;

struct node {
    float f, g, heuristic;
    int parent;
    bool visited = false;
};

class Astar {
    private:
        unordered_map<int, node> nodeInfo;
        priority_queue<pair<float, int>, vector<pair<float, int>>, greater<>> openList;
        unordered_set<int> closedList;

        float predictHeuristic(pair<float, int> currNode, pair<float, int> destNode);
        vector<int> newPath(int start, int dest, terrain &graph);

    public:
    //needed functions: pathfinder, hueristic calulator(g), actual cost calculator(f)
        vector<pair<int,int>> findPath(terrain &graph, pair<int,int> start, pair<int,int> goal);
};
#endif //ASTAR_H
