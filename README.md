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
   Dijkstra’s path
   A*’s path
- Display total cost of path
- Highlight chosen path and terrain using colored tiles

Grid Visualization (via SFML):
Each cell is color-coded:
- White: Clear path (0)
- Light Green → Red: Increasing obstacle weight (1–6)
- Cyan: Cells included in the path
- Additional text display shows the final cost of the path

Setup Instructions:
1. Clone the repo:
git clone https://github.com/yourusername/rover-route-pathfinding.git
cd rover-route-pathfinding
2. Install SFML 3.0.0
Use the MinGW-w64 version
Update CMakeLists.txt with the correct SFML_DIR path
3. Open in CLion or build via CMake:
mkdir build && cd build
cmake ..
make
4. Make sure arial.ttf is in the root directory (for text rendering)

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
1. Add frame-by-frame animation of the algorithms
2. Show explored nodes
3. Benchmark performance on larger grids
4. Add user-selectable heuristics for A*
