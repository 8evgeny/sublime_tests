cmake_minimum_required(VERSION 3.0)

project(advanced_1_types)
add_compile_options( -std=c++14 )
add_executable(${PROJECT_NAME} "main.cpp")
add_custom_command(
    OUTPUT ${PROJECT_NAME}
    COMMAND c++filt -t main.cpp)
