cmake_minimum_required(VERSION 3.7.1)

SET(sourcefile Source.cpp interval_tree.cpp interval_tree_node.cpp range_tree.cpp range_tree_node.cpp func.cpp)

add_executable(orthogonal_window_query ${sourcefile})

