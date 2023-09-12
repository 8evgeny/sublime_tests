cmake_minimum_required(VERSION 3.5)

project(C++20_in_detail LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME}_char8Str CoreLanguage/char8Str.cpp)

