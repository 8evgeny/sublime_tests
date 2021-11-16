cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra")

project(Videokurs_8_Patterns)

add_subdirectory(1_Behavioral)
add_subdirectory(2_Visitor)
#add_subdirectory(3_Creational)
#add_subdirectory(4_Structural-adapter-decorator)
#add_subdirectory(5_Structural-facade-proxy)
