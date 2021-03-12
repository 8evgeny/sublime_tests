cmake_minimum_required(VERSION 3.5)

project(huffman LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(decoding_old decoding_old.cpp)
add_executable(coding_old coding_old.cpp)
