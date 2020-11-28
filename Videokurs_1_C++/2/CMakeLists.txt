cmake_minimum_required(VERSION 3.5)

project(cpp14_1)

add_executable(2_auto auto.cpp)
add_executable(2_lambda lambda.cpp)
add_executable(2_tuple tuple.cpp)

set_target_properties(2_auto 2_lambda 2_tuple PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
        )
