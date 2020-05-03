cmake_minimum_required(VERSION 2.8)
project(a2-ece650)
set (CMAKE_CXX_FLAGS "-std=c++11 -Wall ${CMAKE_CXX_FLAGS}")
set(LIBSRC graph.cpp graph.h)
add_library(graph ${LIBSRC})
add_executable(a2-ece650 a2-ece650.cpp)
target_link_libraries(a2-ece650 graph)
set_target_properties(a2-ece650 PROPERTIES COMPILE_FLAGS "-DUSE_GRAPH")

