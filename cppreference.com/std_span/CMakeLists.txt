cmake_minimum_required(VERSION 3.5)

project(std_span)

add_executable(${PROJECT_NAME} std_span.cpp)


set_target_properties(${PROJECT_NAME}  PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
    )
