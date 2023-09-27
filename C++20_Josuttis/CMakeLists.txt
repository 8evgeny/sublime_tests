cmake_minimum_required(VERSION 3.5)

project(C++20_Josuttis LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME}_17_5_syncstream lib/17_5_syncstream.cpp)
add_executable(${PROJECT_NAME}_17_5_syncfilestream2 lib/17_5_syncfilestream2.cpp)
add_executable(${PROJECT_NAME}_18_5_source_location lib/18_5_sourceloc.cpp)


target_link_libraries(${PROJECT_NAME}_17_5_syncstream pthread)
target_link_libraries(${PROJECT_NAME}_17_5_syncfilestream2 pthread)
