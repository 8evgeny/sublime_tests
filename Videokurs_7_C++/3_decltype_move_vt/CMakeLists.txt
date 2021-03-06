cmake_minimum_required(VERSION 3.5)

project(cpp14_2)

add_executable(3_decltype decltype.cpp)
add_executable(3_move move.cpp)
add_executable(3_vt vt.cpp)

set_target_properties(3_decltype 3_move 3_vt PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
        )
