# Pathfinding-Performance-Analysis
This project compares the performance of A* and Dijkstra’s Algorithm for pathfinding across a randomly generated, weighted terrain grid. Built using C++ and SFML, the application visualizes obstacle-heavy maps and highlights the paths chosen by each algorithm, along with their cost and total distance.

Project Motivation:
In robotics and autonomous navigation, choosing the most efficient pathfinding algorithm is critical. This project simulates a rover navigating through a 2D grid with variable obstacle intensities (weights from 0–6) and compares:
- Path length and cost
- Nodes explored
- Visual clarity of the route

Features:
- Generate a random weighted grid map
- Assign obstacle weights from 0 (no obstacle) to 6 (impassable)
- Compute and visualize:
   - Dijkstra’s path
   - A*’s path
- Display total cost of path
- Highlight chosen path


Setup Instructions:
1. Clone the repo:
- git clone https://github.com/yourusername/rover-route-pathfinding.git
- cd rover-route-pathfinding
2. Open in CLion or build via CMake:
- mkdir build && cd build
- cmake ..
- make

When running the program:
- Enter the number of rows and columns
- Provide source and destination coordinates in format [row,column]
- Watch Dijkstra and A* do their thing

Algorithm Details:
A* ~
Uses Euclidean distance as heuristic,
Prioritizes nodes with lowest f = g + h cost

Dijkstra ~
Uniform-cost search,
Explores all shortest paths exhaustively (no heuristic)


Future Improvements!!!
1. Add a better display of the algorithms at worrk, ideally using SFML
2. Show explored nodes
3. Benchmark performance on larger grids
4. Add user-selectable heuristics for A*
