//
// Created by taylor on 8/1/2025.
//

#include "Astar.h"
#include <algorithm>
#include <unordered_map>
#include <cmath>
#include <sstream>
#include <iostream>
using namespace std;

//constructor
Astar::Astar() {
    while (!openList.empty()) {
        openList.pop();
    }
    closedList.clear();
    nodeInfo.clear();
}

//returns the path taken as a vector of coordinates
vector<pair<int, int>> Astar::newPath(pair<int, int> start, pair<int, int> dest, terrain &graph) {
    vector<pair<int, int>> path;
    int current = graph.getIndexCoordinate(dest);
    int startIndex = graph.getIndexCoordinate(start);

    //working backwards from the destination to return a vector of the new path
    while (current != startIndex) {
        path.push_back(graph.getCoordFromIndex(current));
        current = nodeInfo[current].parent;
    }

    //adding the starting coord and then putting the path in chronological order
    path.push_back(start);
    reverse(path.begin(), path.end());
    return path;
}

float Astar::predictHeuristic(pair<float, int> currNode, pair<float, int> destNode) {
    //using the pythagorean theorem since our grid is theoretically all diagonals right now for data simplicity

    float heuristic = sqrt(pow(currNode.first - destNode.first, 2) + pow(currNode.second - destNode.second, 2));
    return heuristic;
}

vector<pair<int,int>> Astar::algorithm(terrain &graph, pair<int,int> start, pair<int,int> dest) {
    //clearing old data:
    nodeInfo.clear();
    while (!openList.empty()) openList.pop();
    closedList.clear();

    //algorithm starts
    int begin = graph.getIndexCoordinate(start);
    int end = graph.getIndexCoordinate(dest);

    //assigning node data and pushing it to the priority queue
    nodeInfo[begin] = {0.0f, 0.0f, predictHeuristic(start, dest), -1};
    openList.push({nodeInfo[begin].f, begin});

    while (!openList.empty()) {
        pair<float, int> currNode = openList.top();
        float fCost = currNode.first;
        int currentNode = currNode.second;
        openList.pop();

        //reached the end of the path
        if (currentNode == end) {
            vector<pair<int, int>> indices = newPath(start, dest, graph);
            vector<pair<int, int>> coordinates;
            for (auto &index : indices) {
                coordinates.push_back(index);
            }
            return coordinates;
        }

        closedList.insert(currentNode);

        for (auto &edge : graph.getNeighbors(currentNode)) {
            int nextNode = edge.first;
            float weight = edge.second;

            if (closedList.count(nextNode)) {
                continue;
            }

            float gCost = nodeInfo[currentNode].g + weight;

            //if neighbor is unseen or there's a cheaper path found
            if (!nodeInfo.count(nextNode) || gCost < nodeInfo[nextNode].g) {
                nodeInfo[nextNode].heuristic = predictHeuristic(graph.getCoordFromIndex(nextNode), dest);
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

vector<pair<int, int>> Astar::findPath(string source, string dest) {
    //taking the user input (a string) and turning it into a pair of ints to be able to use in my algorithm function
    vector<pair<int, int>> toAndFrom;

    //from coordinates
    stringstream fromstream(source);
    int x, y;
    char characters;
    fromstream >> characters >> x >> characters >> y >> characters;
    pair<int, int> from(x, y);
    toAndFrom.push_back(from);

    //to coordinates
    stringstream tostream(dest);
    tostream >> characters >> x >> characters >> y >> characters;
    pair<int, int> to(x, y);
    toAndFrom.push_back(to);

    return toAndFrom;
}


//getter functions
float Astar::getHeuristic(pair<int, int> currNode, pair<int, int> destNode) {
    return predictHeuristic(currNode, destNode);
}

float Astar::getTotalDistance(vector<pair<int, int>> &path, terrain &graph) {
    float totalDistance = 0;

    //starting form 1 instead of 0 so that it doesn't access an index that doesn't exist
    for (int i = 1; i < path.size(); i++) {
        int fromIndex = graph.getIndexCoordinate(path[i-1]);
        int toIndex = graph.getIndexCoordinate(path[i]);

        auto &neighbors = graph.getNeighbors(fromIndex);

        for (auto &edge : neighbors) {
            if (edge.first == toIndex) {
                totalDistance += edge.second;
                break;
            }
        }
    }

    return totalDistance;
}
