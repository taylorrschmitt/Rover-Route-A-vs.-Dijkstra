//
// Created by Evan Schroeder on 7/31/25.
//
//when creating a grid to test, if 100,000 nodes is wanted, input 317 rows and 317 columns
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

    //Iterate through all the cells in our grid -> for each cell make edges in the graph to all teh cells around it

    int VertexNum;
    pair<int,int> to;
    pair<int, int> from;
    for(int i = 0; i < grid.size(); i++){
        for(int j = 0; j < grid.at(i).size(); j++) {
            populateVertex(j,i, grid);
            from = {j,i};
            if(i != 0) {
                //top
                to = {j, i - 1};
                populateHelper(from, to, grid, 1);
            }
            if(i != 0 && j != grid.at(i).size() -1) {
                //top-right
                to = {j + 1, i - 1};
                populateHelper(from, to, grid, 1.41);
            }
            if(j != grid.at(i).size() - 1) {
                //right
                to = {j + 1, i};
                populateHelper(from, to, grid, 1);
            }
            if(j != grid.at(i).size() && i != grid.size() - 1) {
                //bottom right
                to = {j + 1, i + 1};
                populateHelper(from, to, grid, 1.41);
            }
            if(i != grid.size() - 1) {
                //bottom
                to = {j, i + 1};
                populateHelper(from, to, grid, 1);
            }
            if(i != grid.size() -  1 && j != 0) {
                //bottom left
                to = {j - 1, i + 1};
                populateHelper(from, to, grid, 1.41);
            }
            if(j != 0) {
                //left
                to = {j - 1, i};
                populateHelper(from, to, grid, 1);
            }
            if(j != 0 && i != 0) {
                //top left
                to = {j - 1, i - 1};
                populateHelper(from, to, grid, 1.41);
            }
        }
    }
}

void terrain::populateHelper(pair<int, int> from, pair<int, int> to, vector<vector<int>>& grid, float factor){

   //Make a new vertex from "from" to "to"

    populateVertex(to.first, to.second, grid);
    pair<int, int> newEdge;
    newEdge.first = reverseMapper[to];
    newEdge.second = grid[to.second][to.first] * factor;
    adjacencyList[reverseMapper[from]].push_back(newEdge);
}

void terrain::populateVertex(int x, int y, vector<vector<int>>& grid){

    //Check if the pair we are looking at is in our graph, if not then add it

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
            int value = rand() % 6;
            grid[i][j] = value;
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

void terrain::printAdjacencyList(){
    for(auto it = adjacencyList.begin(); it != adjacencyList.end(); it++) {
        cout << it->first << " -> ";
        for (int i = 0; i < it->second.size(); i++) {
            cout << it->second.at(i).first << " " << it->second.at(i).second << ", ";
        }
        cout << endl;
    }
}