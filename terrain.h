#include<unordered_map>
#include<utility>
#include<vector>
#include<random>
#include<set>

using namespace std;
#ifndef PATHFINDING_PERFORMANCE_ANALYSIS_TERRAIN_H
#define PATHFINDING_PERFORMANCE_ANALYSIS_TERRAIN_H


class terrain {
    unordered_map<int, vector<int>> adjacencyList;
    unordered_map<int, pair<int, int>> mapper;
    unordered_map<pair<int,int>, int> reverseMapper;
public:
    terrain();
    void populateGraph(vector<vector<int>> grid);

};


#endif //PATHFINDING_PERFORMANCE_ANALYSIS_TERRAIN_H
