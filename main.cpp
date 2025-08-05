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
    while(true){
        int rows, columns;
        string from, to;
        terrain graph;

        cout << "Please enter the number of rows and columns: ";
        cin >> rows;
        columns = rows;

        cout << "From: ";
        cin >> from;

        cout << "To: ";
        cin >> to;

        stringstream fromStream(from);
        int xFrom, yFrom, xTo, yTo;
        char dummy;

        fromStream >> dummy >> xFrom >> dummy >> yFrom >> dummy;
        pair<int, int> fromCoords(xFrom,yFrom);

        stringstream toStream(to);
        toStream >> dummy >> xTo >> dummy >> yTo >> dummy;
        pair<int, int> toCoords(xTo,yTo);

        if(xFrom < 0 || xFrom >= columns || xTo < 0 || xTo >= columns || yFrom < 0 || yFrom >= rows || yTo < 0 || yTo >= rows){
            cout << "Coordinates outside of range" << endl;
            cout << endl;
            continue;
        }

        vector<vector<int>> grid = graph.createNodes(rows, columns);
        graph.populateGraph(grid);
        cout << endl;

        Dijkstra DAlg(rows,columns,graph);
        vector<pair<int, int>> path = DAlg.getShortestPath(from, to);

        cout << "Dijkstra's shortest path: " << endl;
        for(int i = 0; i < path.size() - 1; i++){
            cout << "[" << path.at(i).first << ", " << path.at(i).second << "] ->";
        }
        cout<<"[" << path.at(path.size()-1).first << ", " << path.at(path.size()-1).second << "] " << endl;

        cout << "Shortest Distance: " <<  DAlg.getShortestDistance(from, to) << endl;
        cout <<endl;

        Astar AAlg;

        vector<pair<int, int>> AStarCoords = AAlg.findPath(from, to);
        pair<int, int> fromCoord = AStarCoords.at(0);
        pair<int, int> toCoord = AStarCoords.at(1);
        vector<pair<int, int>> AstarPath = AAlg.algorithm(graph, fromCoord, toCoord);

        if (AstarPath.empty()) {
            cout << "No path found by A*." << endl;
        } else {
            cout << "A* shortest path: " << endl;
            for (const auto &p : AstarPath) {
                cout << "[" << p.first << ", " << p.second << "] ->";
            }
            cout << " End" << endl;
            cout << endl;
            cout << "Total Cost: " << AAlg.getTotalDistance(AstarPath, graph) << endl;
        }
        cout << endl;

        string printList;
        cout << "Print Adjacency List? : Y/N" << endl;
        cin >> printList;
        if(printList == "Y"){
            graph.printAdjacencyList();
        }

        string cont;
        cout << "Continue?: Y/N" << endl;
        cin >> cont;
        if(cont == "Y"){
            continue;
        }else{
            break;
        }

    }

    return 0;
}