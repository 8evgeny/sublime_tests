cmake_minimum_required(VERSION 3.5)

set (name vector)
project(STL_${name} LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

#file( GLOB src *.cpp *.h )
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
#find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

add_executable(${PROJECT_NAME}_1 ${name}1.cpp)
add_executable(${PROJECT_NAME}_2 ${name}2.cpp)
add_executable(${PROJECT_NAME}_3 ${name}3.cpp)
#target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
