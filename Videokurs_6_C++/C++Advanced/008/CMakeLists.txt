cmake_minimum_required(VERSION 2.8)

project(advanced_8_STL_C++)
add_compile_options( -std=c++14 -v )
file(GLOB SOURCES
    ./*.h
    ./*.hpp
    ./*.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
