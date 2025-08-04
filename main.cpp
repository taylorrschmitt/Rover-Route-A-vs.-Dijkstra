//
// Created by taylor on 8/1/2025.
//
#include <iostream>
#include <ostream>
#include "terrain.h"
#include "Astar.h"
#include "Dijkstra.h"

using namespace std;

int main() {
    int rows, columns;
    string from, to;

    cout << "Please enter the number of rows: ";
    cin >> rows;
    cout << endl;

    cout << "Please enter the number of columns: " ;
    cin >> columns;
    cout << endl;

    cout << "From: ";
    cin >> from;
    cout << endl;

    cout << "To: ";
    cin >> to;
    cout << endl;

    terrain graph;
    vector<vector<int>> grid = graph.createNodes(rows, columns);
    graph.populateGraph(grid);
    cout << endl;

    Dijkstra testDijkstra(rows,columns,graph);
    vector<pair<int, int>> path = testDijkstra.getShortestPath(from, to);

    cout << "Dijkstra's shortest path: " << endl;
    for(int i = 0; i < path.size(); i++){
        cout << "[" << path.at(i).first << ", " << path.at(i).second << "] ->";
    }
    cout << endl;
    cout << "Shortest Distance: " <<  testDijkstra.getShortestDistance(from, to) << endl;

    Astar testAstar;
    //testDijkstra.~Dijkstra();

    return 0;
}