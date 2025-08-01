//
// Created by taylor on 8/1/2025.
//
#include <iostream>
#include <ostream>
#include "terrain.h"
using namespace std;

int main() {
    int rows, columns;
    cout << "Please enter the number of rows: " << endl;
    cin >> rows;
    cout << "Please enter the number of columns: " << endl;
    cin >> columns;

    terrain graph;
    graph.createNodes(rows, columns);
    cout << endl;
    graph.printAdjacencyList();

    return 0;
}