cmake_minimum_required(VERSION 3.7)
project(perceptrionImpl)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp perceptronFunctions.h perceptronFunctions.cpp)
add_executable(perceptrionImpl ${SOURCE_FILES})