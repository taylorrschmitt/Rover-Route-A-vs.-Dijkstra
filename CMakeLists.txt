cmake_minimum_required(VERSION 3.29)
project(Pathfinding_Performance_Analysis)

set(CMAKE_CXX_STANDARD 17)

set(SFML_DIR "C:/Users/taylo/Downloads/SFML-3.0.0-windows-gcc-14.2.0-mingw-64-bit/SFML-3.0.0/lib/cmake/SFML")

find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)

add_executable(Pathfinding_Performance_Analysis
        terrain.cpp
        terrain.h
        main.cpp
        Dijkstra.cpp
        Dijkstra.h
        Astar.cpp
        Astar.h)


target_include_directories(Pathfinding_Performance_Analysis PRIVATE
        "C:/Users/taylo/Downloads/SFML-3.0.0-windows-gcc-14.2.0-mingw-64-bit/SFML-3.0.0/include")

target_link_libraries(Pathfinding_Performance_Analysis
        "C:/Users/taylo/Downloads/SFML-3.0.0-windows-gcc-14.2.0-mingw-64-bit/SFML-3.0.0/lib/libsfml-graphics.a"
        "C:/Users/taylo/Downloads/SFML-3.0.0-windows-gcc-14.2.0-mingw-64-bit/SFML-3.0.0/lib/libsfml-window.a"
        "C:/Users/taylo/Downloads/SFML-3.0.0-windows-gcc-14.2.0-mingw-64-bit/SFML-3.0.0/lib/libsfml-system.a"
)