cmake_minimum_required(VERSION 3.22)
project(openCL_project_1_min_max LANGUAGES CXX)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package( OpenCL REQUIRED )
find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Gui Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Gui Widgets REQUIRED)

include_directories (${OpenCL_INCLUDE_DIRS} )
include_directories (${CMAKE_SOURCE_DIR} )
set (CMAKE_C_FLAGS "-std=c99 -Wall -DUNIX ${COMPILE_ARCH}")

add_subdirectory(find_min_max)
