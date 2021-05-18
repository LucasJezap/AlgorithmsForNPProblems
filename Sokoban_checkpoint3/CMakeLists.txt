cmake_minimum_required(VERSION 3.17)
project(Sokoban)

set(CMAKE_CXX_STANDARD 14)

add_executable(main main.cpp)
add_executable(checkpoint2 checkpoint2.cpp)
add_executable(find_path find_path.cpp)
add_executable(best_first_search best_first_search.cpp)
add_executable(find_path_recursive find_path_recursive.cpp)
add_executable(best_first_search_recursive best_first_search_recursive.cpp)
add_executable(best_first_search_no_file best_first_search_no_file.cpp)
