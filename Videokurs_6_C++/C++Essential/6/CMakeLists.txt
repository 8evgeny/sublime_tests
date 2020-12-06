cmake_minimum_required(VERSION 2.8)

project(essential_6_Templates)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
file(GLOB SOURCES
    ./*.h
    ./*.cpp
)
add_executable(${PROJECT_NAME} ${SOURCES})
