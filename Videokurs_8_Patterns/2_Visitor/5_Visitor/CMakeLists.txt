cmake_minimum_required(VERSION 3.5)

project(Visitor_visitor)

add_executable(${PROJECT_NAME}  visitor.cpp)


set_target_properties(${PROJECT_NAME}  PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
        )
