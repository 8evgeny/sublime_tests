cmake_minimum_required(VERSION 2.8)

project(advanced_11_work_with_files)
set(CMAKE_CXX_FLAGS "-std=c++11 -static-libstdc++")
set(CMAKE_EXE_LINKER_FLAGS "-static-libstdc++")
#add_compile_options( -pedantic -std=c++17 -lc++experimental -lc++fs -v )
file(GLOB SOURCES
    ./*.h
    ./*.hpp
    ./*.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
