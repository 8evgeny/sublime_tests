cmake_minimum_required(VERSION 3.5)

project(CXX_geek LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME}_tokenize_string tokenize_string.cpp)
add_executable(${PROJECT_NAME}_string_contain_only_letters string_contain_only_letters.cpp)
