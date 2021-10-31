cmake_minimum_required(VERSION 3.5)

project(mathematical_constants)

add_executable(${PROJECT_NAME} mathematical_constants.cpp)

#set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_BUILD_TYPE debug)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a")

set_target_properties(${PROJECT_NAME}  PROPERTIES
#    CXX_STANDARD 17
    CXX_STANDARD 20
    CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a"
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
    )
