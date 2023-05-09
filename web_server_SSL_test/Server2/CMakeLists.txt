cmake_minimum_required(VERSION 3.5)

set (name web_server_SSL_test2)
project(${name} LANGUAGES CXX)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file (GLOB SRC *.cpp)

find_package(Qt5Core)
find_package(Qt5Network)
add_executable(${name} ${SRC} )

set_target_properties(${name}   PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
    )

target_link_libraries(${name} Qt5::Core Qt5::Network)

