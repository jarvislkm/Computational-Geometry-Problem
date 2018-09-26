cmake_minimum_required(VERSION 3.7.1)

project(Orthogonal-window-query)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

ADD_SUBDIRECTORY(src)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/data/data.txt
	DESTINATION ${CMAKE_BINARY_DIR}/bin)
