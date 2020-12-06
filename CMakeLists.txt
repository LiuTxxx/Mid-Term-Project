cmake_minimum_required(VERSION 3.16)
project(Assignment4)

set(CMAKE_CXX_STANDARD 14)

add_executable(Assignment4 testMat.cpp Matrix.cpp Matrix.h)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -fopenmp")