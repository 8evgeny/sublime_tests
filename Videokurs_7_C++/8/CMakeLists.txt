cmake_minimum_required(VERSION 3.5)

project(allocator)

add_executable(8_allocator allocator.cpp)

set_target_properties(8_allocator PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
        )
