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

    //dijkstra testing
    Dijkstra testDijkstra(rows,columns,graph);
    vector<pair<int, int>> path = testDijkstra.getShortestPath(from, to);

    cout << "Dijkstra's shortest path: " << endl;
    for(int i = 0; i < path.size(); i++){
        cout << "[" << path.at(i).first << ", " << path.at(i).second << "] ->";
    }
    //cout << " End" << endl;
    cout << endl;
    cout << "Shortest Distance: " <<  testDijkstra.getShortestDistance(from, to) << endl;
    cout << endl;

    cout << endl;

    graph.printAdjacencyList();
    /*
    Astar testAstar;

    vector<pair<int, int>> AStarCoords = testAstar.findPath(from, to);
    pair<int, int> fromCoord = AStarCoords.at(0);
    pair<int, int> toCoord = AStarCoords.at(1);
    vector<pair<int, int>> AstarPath = testAstar.algorithm(graph, fromCoord, toCoord);

    if (AstarPath.empty()) {
        cout << "No path found by A*." << endl;
    } else {
        cout << "A* shortest path: " << endl;
        for (const auto &p : AstarPath) {
            cout << "[" << p.first << ", " << p.second << "] ->";
        }
        cout << " End" << endl;
        cout << endl;
        cout << "Total Cost: " << testAstar.getTotalDistance(AstarPath, graph) << endl;
    }
    */
    cout << endl;

    return 0;
}