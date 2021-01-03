cmake_minimum_required(VERSION 3.17)

set(BOOST_ROOT "/home/mdano/Documents/boost_1_73_0")

find_package(Boost 1.73.0)
if (NOT Boost_FOUND)
    message(FATAL_ERROR "Could not find boost!")
endif ()
project(Algo)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
add_executable(Algo main.cpp mylibs/Partition.h mylibs/Queens.h mylibs/UnionFind.h mylibs/Trie.h mylibs/SegmentTree.h mylibs/graph/Graph_multiple_cost_children.h mylibs/Knapsack01.h mylibs/String.h mylibs/Calculator.h mylibs/graph/Graph_children.h mylibs/graph/Graph_parents.h mylibs/graph/Graph_vertices.h)