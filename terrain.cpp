//
// Created by Evan Schroeder on 7/31/25.
//
//when creating a grid to test, if 100,000 nodes is wanted, input 317 rows and 317 columns
#include "terrain.h"
#include <iostream>
#include <vector>
#include <algorithm>
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
            pair<int, int> from = {j,i};

            //creating vectors for the coordinates of directions and their weights
            vector<pair<int, int>> directions = {
                {0, -1},  {1, -1},  {1, 0},  {1, 1}, {0, 1},   {-1, 1},  {-1, 0}, {-1, -1}
            };
            vector<float> directionWeights = {
                1.0, 1.41, 1.0, 1.41, 1.0, 1.41, 1.0, 1.41
            };
            //randomizing the direction of edges and the number of edges for each vertex
            vector<int> edgeDirections = {0,1,2,3,4,5,6,7};
            random_shuffle(edgeDirections.begin(), edgeDirections.end());
            int numOfEdges = rand() % 6;

            for (int k = 0; k < numOfEdges; k++) {
                int newDirec = edgeDirections[k];
                int newX = directions[newDirec].first + j;
                int newY = directions[newDirec].second + i;

                if (newX >= 0 && newX < grid[0].size() && newY >= 0 && newY < grid.size()) {
                    pair<int, int> to = {newX, newY};
                    populateHelper(from, to, grid, directionWeights[newDirec]);
                }
            }

            // if(i != 0) {
            //     //top
            //     to = {j, i - 1};
            //     populateHelper(from, to, grid, 1);
            // }
            // if(i != 0 && j != grid.at(i).size() -1) {
            //     //top-right
            //     to = {j + 1, i - 1};
            //     populateHelper(from, to, grid, 1.41);
            // }
            // if(j != grid.at(i).size() - 1) {
            //     //right
            //     to = {j + 1, i};
            //     populateHelper(from, to, grid, 1);
            // }
            // if(j != grid.at(i).size() - 1 && i != grid.size() - 1) {
            //     //bottom right
            //     to = {j + 1, i + 1};
            //     populateHelper(from, to, grid, 1.41);
            // }
            // if(i != grid.size() - 1) {
            //     //bottom
            //     to = {j, i + 1};
            //     populateHelper(from, to, grid, 1);
            // }
            // if(i != grid.size() -  1 && j != 0) {
            //     //bottom left
            //     to = {j - 1, i + 1};
            //     populateHelper(from, to, grid, 1.41);
            // }
            // if(j != 0) {
            //     //left
            //     to = {j - 1, i};
            //     populateHelper(from, to, grid, 1);
            // }
            // if(j != 0 && i != 0) {
            //     //top left
            //     to = {j - 1, i - 1};
            //     populateHelper(from, to, grid, 1.41);
            // }
        }
    }
}

void terrain::populateHelper(pair<int, int> from, pair<int, int> to, vector<vector<int>>& grid, float factor){

   //Make a new vertex from "from" to "to"
    populateVertex(to.first, to.second, grid);
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
    srand(time(0));

    //creating 2d vector of nodes with values ranging from 0-5 for type of obstacle
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int value = rand() % 6 + 1;
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