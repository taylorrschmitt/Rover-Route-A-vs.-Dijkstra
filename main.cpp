//
// Created by taylor on 8/1/2025.
//
#include <iostream>
#include <ostream>
#include "terrain.h"
#include "Astar.h"
#include "Dijkstra.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace std;

sf::Color tileColors(int weight) {
    switch (weight) {
        case 0: return sf::Color::White; //no obstacle
        case 1: return sf::Color(200, 255, 200); //light green light obstacle
        case 2: return sf::Color(100, 250, 100);
        case 3: return sf::Color::Yellow;
        case 4: return sf::Color(255, 165, 0);
        case 6: return sf::Color::Red;
        default: return sf::Color::Black; //unknown
    }
}

void drawGrid(sf::RenderWindow &window, const vector<vector<int>> &grid, const vector<pair<int, int>> &pathCoords = {}) {
    int tileSize = 20;
    for (int row = 0; row< grid.size(); row++) {
        for (int col = 0; col< grid[0].size(); col++) {
            int positionX = col * tileSize;
            int positionY = row * tileSize;
            sf::RectangleShape tile(sf::Vector2f(tileSize, tileSize));
            tile.setPosition(sf::Vector2f(positionX, positionY));
            tile.setFillColor(tileColors(grid[row][col]));

            //if tile is already part of the path, override the color
            // if (find(pathCoords.begin(), pathCoords.end(), make_pair(row, col)) != pathCoords.end()) {
            //     tile.setFillColor(sf::Color::Cyan);
            // }

            tile.setOutlineColor(sf::Color::Black);
            tile.setOutlineThickness(1);
            window.draw(tile);
        }
    }
}

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
    //cout << " End" << endl;
    cout << endl;
    cout << "Shortest Distance: " <<  testDijkstra.getShortestDistance(from, to) << endl;
    cout << endl;

    graph.printAdjacencyList();
    cout << endl;

    //Astar testing
    Astar testAstar;

    vector<pair<int, int>> AStarCoords = testAstar.findPath(from, to);
    pair<int, int> fromCoord = AStarCoords.at(0);
    pair<int, int> toCoord = AStarCoords.at(1);
    vector<pair<int, int>> AstarPath = testAstar.algorithm(graph, fromCoord, toCoord);

    if (AstarPath.empty()) {
        cout << "No path found by A*." << endl;
    } else {
        cout << "A* shortest path: " << endl;
        for (const auto &p : AstarPath) {
            cout << "[" << p.first << ", " << p.second << "] ->";
        }
        cout << " End" << endl;
        cout << endl;
        cout << "Total Cost: " << testAstar.getTotalDistance(AstarPath, graph) << endl;
    }

    cout << endl;

    graph.printAdjacencyList();


    //sf::RenderWindow window(sf::VideoMode({static_cast<unsigned>(columns * 20), static_cast<unsigned>(rows * 20)}), "A* Path");

    sf::Font font;
    if (!font.openFromFile("arial.ttf")) {
        std::cerr << "Error loading font\n";
    }

    string costStr = "Cost: " + to_string(testAstar.getTotalDistance(AstarPath, graph));
    sf::Text costText(font, costStr, 20);
    costText.setFillColor(sf::Color::Black);
    costText.setPosition(sf::Vector2f(10, rows * 20 + 5));

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