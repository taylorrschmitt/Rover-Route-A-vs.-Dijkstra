#include<unordered_map>
#include<map>
#include<utility>
#include<vector>
#include<random>
#include<set>

using namespace std;
#ifndef PATHFINDING_PERFORMANCE_ANALYSIS_TERRAIN_H
#define PATHFINDING_PERFORMANCE_ANALYSIS_TERRAIN_H

class terrain {
    int graphIndex;
    unordered_map<int, vector<pair<int,float>>> adjacencyList;
    map<int, pair<int, int>> mapper;
    map<pair<int,int>, int> reverseMapper;
public:
    terrain();
    void populateGraph(vector<vector<int>> grid);
    void populateHelper(pair<int, int> from, pair<int, int> to, vector<vector<int>>& grid, float factor);
    void populateVertex(int x, int y, vector<vector<int>>& grid);

    void printAdjacencyList();

    vector<vector<int>> createNodes(int rows, int cols);
};
#endif //PATHFINDING_PERFORMANCE_ANALYSIS_TERRAIN_H
