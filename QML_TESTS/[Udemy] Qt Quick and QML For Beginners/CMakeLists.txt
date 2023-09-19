cmake_minimum_required(VERSION 3.16)
project(Udremi_QML)
find_package(Qt5 COMPONENTS Widgets Qml Quick REQUIRED)
include_directories(${Qt5Widgets_INCLUDE_DIRS} ${QtQml_INCLUDE_DIRS})
add_definitions(${Qt5Widgets_DEFINITIONS} ${QtQml_DEFINITIONS} ${${Qt5Quick_DEFINITIONS}})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -std=c++17 -fstrict-aliasing -pedantic-errors -pedantic -Wno-deprecated-declarations -Wno-unused-variable")

add_subdirectory(2-2QMLDataTypesDemo)
add_subdirectory(2-1QMLSyntaxDemo)
add_subdirectory(2-3PropertyBindingDemo)
add_subdirectory(2-4QtGlobalObjectDemo)
