cmake_minimum_required(VERSION 2.8)

project(sixth_lesson)
set(CMAKE_CXX_STANDARD 17)

add_compile_options( -std=c++1z )
add_executable(${PROJECT_NAME} "main.cpp")
