cmake_minimum_required(VERSION 3.5)

project(Visitor_strategy)

add_executable(${PROJECT_NAME}_dynamic  strategy_dynamic.cpp)
add_executable(${PROJECT_NAME}_static  strategy_static.cpp)

set_target_properties(${PROJECT_NAME}_static  PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
        )
set_target_properties(${PROJECT_NAME}_dynamic  PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
        )
