cmake_minimum_required(VERSION 3.5)

project(C++20_Josuttis LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -pthread -fcoroutines")

#!!!!! sudo apt install libfmt-dev
find_package(fmt)

add_executable(${PROJECT_NAME}_17_1_1_latch lib/17_1_1_latch.cpp)
add_executable(${PROJECT_NAME}_17_1_1_latchready lib/17_1_1_latchready.cpp)
add_executable(${PROJECT_NAME}_17_1_2_barrier lib/17_1_2_barrier.cpp)
target_link_libraries(${PROJECT_NAME}_17_1_2_barrier fmt::fmt)

add_executable(${PROJECT_NAME}_17_5_syncstream lib/17_5_syncstream.cpp)
add_executable(${PROJECT_NAME}_17_5_syncfilestream lib/17_5_syncfilestream.cpp)
add_executable(${PROJECT_NAME}_17_5_syncfilestream2 lib/17_5_syncfilestream2.cpp)
add_executable(${PROJECT_NAME}_18_5_source_location lib/18_5_sourceloc.cpp)




