cmake_minimum_required(VERSION 2.8)

project(advanced_6_Threads2)
set(CMAKE_CXX_STANDARD 17)

add_compile_options( -std=c++1z )

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

