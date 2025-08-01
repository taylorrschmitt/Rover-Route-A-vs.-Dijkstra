cmake_minimum_required(VERSION 3.29)
project(Pathfinding_Performance_Analysis)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Pathfinding_Performance_Analysis
        terrain.cpp
        terrain.h
        main.cpp)
