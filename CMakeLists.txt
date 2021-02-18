cmake_minimum_required(VERSION 3.0.0)
project(alog VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(alog bfs.cpp heap_problem.cpp dp_problem.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
add_definitions(-std=c++14)
include(CPack)
