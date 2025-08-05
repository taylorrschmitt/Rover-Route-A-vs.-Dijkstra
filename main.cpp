//
// Created by taylor on 8/1/2025.
//
#include <iostream>
#include <ostream>
#include "terrain.h"
#include "Astar.h"
#include "Dijkstra.h"
// #include <SFML/Graphics.hpp>
//#include <SFML/Window.hpp>

using namespace std;
//
// sf::Color tileColors(int weight) {
//     switch (weight) {
//         case 0: return sf::Color::White; //no obstacle
//         case 1: return sf::Color(200, 255, 200); //light green light obstacle
//         case 2: return sf::Color(100, 250, 100);
//         case 3: return sf::Color::Yellow;
//         case 4: return sf::Color(255, 165, 0);
//         case 6: return sf::Color::Red;
//         default: return sf::Color::Black; //unknown
//     }
// }
//
// void drawGrid(sf::RenderWindow &window, const vector<vector<int>> &grid, const vector<pair<int, int>> &pathCoords = {}) {
//     int tileSize = 20;
//     for (int row = 0; row< grid.size(); row++) {
//         for (int col = 0; col< grid[0].size(); col++) {
//             int positionX = col * tileSize;
//             int positionY = row * tileSize;
//             sf::RectangleShape tile(sf::Vector2f(tileSize, tileSize));
//             tile.setPosition(sf::Vector2f(positionX, positionY));
//             tile.setFillColor(tileColors(grid[row][col]));
//
//             //if tile is already part of the path, override the color
//             // if (find(pathCoords.begin(), pathCoords.end(), make_pair(row, col)) != pathCoords.end()) {
//             //     tile.setFillColor(sf::Color::Cyan);
//             // }
//
//             tile.setOutlineColor(sf::Color::Black);
//             tile.setOutlineThickness(1);
//             window.draw(tile);
//         }
//     }
// }

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


    //sf::RenderWindow window(sf::VideoMode({static_cast<unsigned>(columns * 20), static_cast<unsigned>(rows * 20)}), "A* Path");

    // sf::Font font;
    // if (!font.openFromFile("arial.ttf")) {
    //     std::cerr << "Error loading font\n";
    // }
    //
    // string costStr = "Cost: " + to_string(testAstar.getTotalDistance(AstarPath, graph));
    // sf::Text costText(font, costStr, 20);
    // costText.setFillColor(sf::Color::Black);
    // costText.setPosition(sf::Vector2f(10, rows * 20 + 5));

    // sf::Event event;
    //
    // while (window.isOpen()) {
    //     while (window.pollEvent(event)) {
    //         if (event.type == sf::Event::Closed())
    //             window.close();
    //     }
    //
    //     window.clear();
    //     drawGrid(window, grid, AstarPath);
    //     window.draw(costText);
    //     window.display();
    // }
    return 0;
}