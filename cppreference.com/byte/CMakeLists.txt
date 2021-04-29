cmake_minimum_required(VERSION 3.5)

project(byte)

add_executable(${PROJECT_NAME} byte.cpp)


set_target_properties(${PROJECT_NAME}  PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
    )
