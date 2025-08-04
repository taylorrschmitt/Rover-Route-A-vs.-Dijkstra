//
// Created by taylor on 8/1/2025.
//

#include "Astar.h"
#include <algorithm>
#include <unordered_map>
#include <cmath>
using namespace std;


vector<pair<int, int>> Astar::newPath(int start, int dest, terrain &graph) {
    vector<pair<int, int>> path;
    int current = dest;
    while (current != start) {
        path.push_back(graph.mapper[current]);
        current = nodeInfo[current].parent;
    }
    path.push_back(start);
    reverse(path.begin(), path.end());
    return path;
}

float Astar::predictHeruistic(pair<float, int> currNode, pair<float, int> destNode) {
    return sqrt(pow(currNode.first - destNode.first, 2) + pow(currNode.second - destNode.second, 2));
}

vector<pair<int,int>> Astar::findPath(terrain &graph, pair<int,int> start, pair<int,int> dest) {
    int begin = graph.reverseMapper[start];
    int end = graph.reverseMapper[dest];
    nodeInfo[begin] = {0.0f, 0.0f, predictHeuristic(start, dest), -1};

    openList.push({nodeInfo[begin].f, begin});

    while (!openList.empty()) {
        pair<float, int> currNode = openList.top();
        float fCost = currNode.first;
        int currentNode = currNode.second;
        openList.pop();

        //reached the end of the path
        if (currentNode == end) {
            vector<int> indices = newPath(begin, end, graph);
            vector<vector<int, int>> coordinates;
            for (int i = 0; i < indices.size(); i++) {
                coordinates.push_back(graph.mapper[i]);
            }
            return coordinates;
        }

        closedList.insert(currentNode);

        for (auto &edge : graph.adjacencyList[currNode]) {
            int nextNode = edge.first;
            float weight = edge.second;

            if (closedList.count(nextNode)) {
                continue;
            }

            float gCost = nodeInfo[currNode].g + weight;
            //if neighbor is unseen or there's a cheaper path found
            if (!nodeInfo.count(nextNode) || gCost < nodeInfo[nextNode].g) {
                nodeInfo[nextNode].heuristic = predictHeuristic(graph.mapper[nextNode], dest);
                nodeInfo[nextNode].g = gCost;
                nodeInfo[nextNode].f = nodeInfo[nextNode].g + nodeInfo[nextNode].heuristic;
                nodeInfo[nextNode].parent = currentNode;
                openList.push({nodeInfo[nextNode].f, nextNode});
            }
        }
    }
    //else, no path was found
    return{};
}