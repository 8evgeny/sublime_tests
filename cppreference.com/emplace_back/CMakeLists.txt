cmake_minimum_required(VERSION 3.5)

project(emplace_back)

add_executable(${PROJECT_NAME} emplace_back.cpp)
add_executable(${PROJECT_NAME}1 emplace_back1.cpp)

set_target_properties(${PROJECT_NAME}  PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
    )
