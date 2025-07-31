//
// Created by Evan Schroeder on 7/31/25.
//

#include "terrain.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

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

vector<vector<int>> terrain::createNodes(int rows, int cols){
    vector<vector<int>> grid;
    srand(time(0));
}