//
// Created by taylo on 8/1/2025.
//

#ifndef ASTAR_H
#define ASTAR_H
#include <queue>
using namespace std;

class Astar {
private:
    priority_queue<int> openList;
    priority_queue<int, vector<int>, greater<int>> closedList;
    int g_cost, f_cost;
    public:
    Astar();
};
#endif //ASTAR_H
