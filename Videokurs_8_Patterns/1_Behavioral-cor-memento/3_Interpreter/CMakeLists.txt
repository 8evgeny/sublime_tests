cmake_minimum_required(VERSION 3.5)

project(Behavioral-cor-memento_Interpreter)

add_executable(${PROJECT_NAME}  interpreter.cpp)


set_target_properties(${PROJECT_NAME}  PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
        )

