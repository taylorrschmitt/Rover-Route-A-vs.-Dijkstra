//
// Created by Evan Schroeder on 7/31/25.
//
//when creating a grid to test, if 100,000 nodes is wanted input 317 rows and 317 columns
#include "terrain.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

terrain::terrain() {
    graphIndex = 0;
}

void terrain::populateGraph(vector<vector<int>> grid){
    int VertexNum;
    for(int i = 0; i < grid.size(); i++){
        for(int j = 0; j < grid.at(i).size(); j++) {
            if(i == 0){
                if(j == 0){

                }
            }
        }
    }
}

void terrain::populateVertex(int x, int y, vector<vector<int>>){
    pair<int, int> myPair(x,y);
    if(adjacencyList.find(reverseMapper[myPair]) == adjacencyList.end()){
        mapper[graphIndex] = myPair;
        reverseMapper[myPair] = graphIndex;
        adjacencyList[graphIndex] = {};
        graphIndex++;
    }
}




vector<vector<int>> terrain::createNodes(int rows, int cols){
    vector<vector<int>> grid;
    srand(time(0));

    //creating 2d vector of nodes with values ranging from 0-5 for type of obstacle
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            grid.push_back(vector<int>(rand() % 6));
        }
    }

    //printing the grid
    for (const auto &row : grid) {
        for (const auto &value : row) {
            cout << value << " ";
        }
        cout << endl;
    }

    return grid;
}