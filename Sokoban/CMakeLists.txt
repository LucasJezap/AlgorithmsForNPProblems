cmake_minimum_required(VERSION 3.17)
project(Sokoban)

set(CMAKE_CXX_STANDARD 14)

add_executable(dfs dfs.cpp)
add_executable(bfs bfs.cpp)
add_executable(uniform uniform_cost.cpp)
add_executable(greedy_best greedy_best_first.cpp)
add_executable(a_star a_star.cpp)