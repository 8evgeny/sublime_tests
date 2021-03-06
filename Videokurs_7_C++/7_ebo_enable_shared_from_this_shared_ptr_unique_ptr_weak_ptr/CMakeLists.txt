cmake_minimum_required(VERSION 3.15)
project(smart_ptr)

set(CMAKE_CXX_STANDARD 17)

add_executable(7_unique_ptr unique_ptr.cpp)
add_executable(7_shared_ptr shared_ptr.cpp)
add_executable(7_weak_ptr weak_ptr.cpp)
add_executable(7_enable_shared_from_this enable_shared_from_this.cpp)
add_executable(7_ebo ebo.cpp)
