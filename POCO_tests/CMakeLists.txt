cmake_minimum_required(VERSION 3.15)
project(POCO_test)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a")

add_subdirectory(conan_poko_timer)
#add_subdirectory(conan_poko_net)
