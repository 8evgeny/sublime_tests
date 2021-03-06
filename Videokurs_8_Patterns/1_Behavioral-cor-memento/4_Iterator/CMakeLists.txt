cmake_minimum_required(VERSION 3.5)

project(Behavioral-cor-memento_Iterator)

add_executable(${PROJECT_NAME}_facade  facade.cpp)
add_executable(${PROJECT_NAME}_iterator  iterator.cpp)

set_target_properties(${PROJECT_NAME}_facade  PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
        )
set_target_properties(${PROJECT_NAME}_iterator  PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
        )
