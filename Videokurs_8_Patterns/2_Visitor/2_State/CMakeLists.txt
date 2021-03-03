cmake_minimum_required(VERSION 3.5)

project(Visitor_state)

add_executable(${PROJECT_NAME}_basic  basic.cpp)
add_executable(${PROJECT_NAME}_msm  msm.cpp)

set_target_properties(${PROJECT_NAME}_basic  PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
        )
set_target_properties(${PROJECT_NAME}_msm  PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
        )
