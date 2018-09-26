cmake_minimum_required(VERSION 3.7.1)

SET(sourcefile Source.cpp range_tree.cpp range_tree_node.cpp func.cpp)

add_executable(planar_point_range_query ${sourcefile})

