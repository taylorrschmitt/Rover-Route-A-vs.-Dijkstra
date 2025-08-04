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

        //keeping these two functions private to only access through the algorithm
        float predictHeuristic(pair<float, int> currNode, pair<float, int> destNode);
        vector<pair<int, int>> newPath(pair<int, int> start, pair<int, int> dest, terrain &graph);

    public:
        Astar();

        vector<pair<int,int>> algorithm(terrain &graph, pair<int,int> start, pair<int,int> goal);
        vector<pair<int, int>> findPath(string source, string dest);

        float getHeuristic(pair<int, int> currNode, pair<int, int> destNode);
        float getTotalDistance(vector<pair<int, int>> &path, terrain &graph);
};

#endif //ASTAR_H
