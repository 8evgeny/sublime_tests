cmake_minimum_required(VERSION 3.5)

set (name Evileg)
project(${name} LANGUAGES CXX)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file (GLOB src *)

find_package(Qt5Core)
add_executable(${PROJECT_NAME}_QString
    ${src}
    )
set_target_properties(${PROJECT_NAME}_QString  PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
    )
target_link_libraries(${PROJECT_NAME}_QString
    Qt5::Core)
#Qt${QT_VERSION_MAJOR}::Core)
