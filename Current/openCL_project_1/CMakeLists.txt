cmake_minimum_required(VERSION 3.22)
project(openCL_project_1 LANGUAGES CXX)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(OpenCV_DIR $ENV{HOME}/opencv/install_4_7_0_contrib_cuda)
find_package(OpenCV REQUIRED PATHS ${OpenCV_DIR} NO_DEFAULT_PATH)
message(OpenCV_INCLUDE_DIRS=${OpenCV_INCLUDE_DIRS})
include_directories(${OpenCV_INCLUDE_DIRS})

find_package( OpenCL REQUIRED )
find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Gui Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Gui Widgets REQUIRED)

include_directories (${OpenCL_INCLUDE_DIRS} )
include_directories (${CMAKE_SOURCE_DIR} )
set (CMAKE_C_FLAGS "-std=c99 -Wall -DUNIX ${COMPILE_ARCH}")

add_subdirectory(0_Simple_add)
add_subdirectory(1_Matching) #SerialMatches реализовано только с OpenCV  (алгоритм не реализован)
add_subdirectory(2_Matching) # GPU vs CPU
add_subdirectory(3_edge)  #  Работают Serial и SerialOpenCV   (Parallel edge не работает  !!!!! )
#add_subdirectory(3_edge2)
#add_subdirectory(3_edge3)

#add_subdirectory(4_image_filtering)

add_subdirectory(5_mandelbrot)
add_subdirectory(6_convertImage)
add_subdirectory(7_copyImage)
