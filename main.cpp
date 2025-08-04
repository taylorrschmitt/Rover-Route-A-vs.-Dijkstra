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
    cout << endl;
    cout << "Shortest Distance: " <<  testDijkstra.getShortestDistance(from, to) << endl;

    graph.printAdjacencyList();
    //Astar testing
    Astar testAstar;
    vector<pair<int, int>> AStarCoords = testAstar.findPath(from, to);
    pair<int, int> fromCoord = AStarCoords.at(0);
    pair<int, int> toCoord = AStarCoords.at(1);
    vector<pair<int, int>> AstarPath = testAstar.algorithm(graph, fromCoord, toCoord);

    cout << "A* shortest path: " << endl;
    for(int i = 0; i < AstarPath.size(); i++) {
        cout << "[" << AstarPath.at(i).first << ", " << AstarPath.at(i).second << "] ->";
    }
    cout << endl;
    cout << "Total Distance: " << testAstar.getTotalDistance(AstarPath, graph) << endl;

    return 0;
}