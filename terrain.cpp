//
// Created by Evan Schroeder on 7/31/25.
//
//to make a graph >100,000 nodes, inupt 317 rows and 317 columns
#include "terrain.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

void terrain::populateGraph()


void terrain::printGraph();


vector<vector<int>> terrain::createInputs(int rows, int cols){
    vector<vector<int>> grid(rows, vector<int>(cols, 0));
    srand(time(0));

}