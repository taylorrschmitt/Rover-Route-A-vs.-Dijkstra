//
// Created by Evan Schroeder on 7/31/25.
//
//when creating a grid to test, if 100,000 nodes is wanted, input 317 rows and 317 columns
#include "terrain.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
using namespace std;

terrain::terrain() {
    graphIndex = 0;
}

void terrain::populateGraph(vector<vector<int>> grid){

    random_device rd;
    mt19937 gen(rd());

    //creating vectors for the coordinates of directions and their weights
    vector<pair<int, int>> directions = {
            {0, -1},  {1, -1},  {1, 0},  {1, 1}, {0, 1},   {-1, 1},  {-1, 0}, {-1, -1}
    };

    vector<float> directionWeights = {
            1.0, 1.41, 1.0, 1.41, 1.0, 1.41, 1.0, 1.41
    };

    //Iterate through all the cells in our grid -> for each cell make edges in the graph to all teh cells around it
    int VertexNum;
    pair<int,int> to;
    for(int i = 0; i < grid.size(); i++){
        for(int j = 0; j < grid.at(i).size(); j++) {
            populateVertex(j,i, grid);
            pair<int, int> from = {j,i};

            vector<int> edgeDirections;
            for(int k = 0; k < directions.size(); k++){
                int newX = j + directions[k].first;
                int newY = i + directions[k].second;

                if(newX >= 0 && newX < grid[0].size() && newY >= 0 && newY < grid.size()){
                    edgeDirections.push_back(k);
                }
            }

            shuffle(edgeDirections.begin(), edgeDirections.end(), gen);
            int maxEdges = edgeDirections.size();
            if(maxEdges == 0){
                continue;
            }

            int numOfEdges = uniform_int_distribution<>(1,maxEdges)(gen);

            for (int k = 0; k < numOfEdges; k++) {
                int newDirec = edgeDirections[k];
                int newX = directions[newDirec].first + j;
                int newY = directions[newDirec].second + i;

                pair<int, int> to = {newX, newY};
                populateHelper(from, to, grid, directionWeights[newDirec]);
            }
        }
    }
}

void terrain::populateHelper(pair<int, int> from, pair<int, int> to, vector<vector<int>>& grid, float factor){
    populateVertex(to.first, to.second, grid);
    //Check if there already is an edge from "from" to "to"
    for(int i = 0; i < adjacencyList[reverseMapper[from]].size(); i++){
        if(adjacencyList[reverseMapper[from]].at(i).first == reverseMapper[to]){
            return;
        }
    }

    //Make a new vertex from "from" to "to"
    pair<int, float> newEdge;
    newEdge.first = reverseMapper[to];
    newEdge.second = grid[to.second][to.first] * factor;
    adjacencyList[reverseMapper[from]].push_back(newEdge);
}

void terrain::populateVertex(int x, int y, vector<vector<int>>& grid){

    //Check if the pair we are looking at is in our graph, if not then add it
    pair<int, int> myPair(x,y);
    if(reverseMapper.find(myPair) == reverseMapper.end()){
        mapper[graphIndex] = myPair;
        reverseMapper[myPair] = graphIndex;
        adjacencyList[graphIndex] = {};
        graphIndex++;
    }
}

vector<vector<int>> terrain::createNodes(int rows, int cols){
    vector<vector<int>> grid(rows, vector<int> (cols));
    random_device rd;
    mt19937 gen(rd());

    //creating 2d vector of nodes with values ranging from 0-5 for type of obstacle
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int value = uniform_int_distribution<>(1,5)(gen);
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

    populateGraph(grid);
    return grid;
}

void terrain::printAdjacencyList(){
    for(auto it = adjacencyList.begin(); it != adjacencyList.end(); it++) {
        pair<int, int> coordinateFrom = mapper[it->first];
        cout << "(" << coordinateFrom.first << ", " << coordinateFrom.second << ")  ->";
        for (int i = 0; i < it->second.size(); i++) {
            int toIndex = it->second.at(i).first;
            float weight = it->second.at(i).second;
            pair<int, int> coordinateTo = mapper[toIndex];
            cout << "(" << coordinateTo.first << ", " << coordinateTo.second << ") weight: " << weight << ", ";
        }
        cout << endl;
    }
}

int terrain::getIndexCoordinate(pair<int, int> cord) const {
    return reverseMapper.at(cord);
}

pair<int, int> terrain::getCoordFromIndex(int index) const {
    return mapper.at(index);
}

const vector<pair<int, float>>& terrain::getNeighbors(int index) {
    return adjacencyList.at(index);
}

unordered_map<int, vector<pair<int,float>>> terrain::getAdjacencyList(){
    return adjacencyList;
}
map<int, pair<int, int>> terrain::getMapper(){
    return mapper;
}
map<pair<int,int>, int> terrain::getReverseMapper(){
    return reverseMapper;
}