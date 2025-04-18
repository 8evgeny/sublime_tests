cmake_minimum_required(VERSION 3.22)
project(openCL_project_neuro_1 LANGUAGES CXX)
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

file(GLOB src *.cpp)

add_executable(CL_neuro_1 ${src})
target_link_libraries(CL_neuro_1
    ${OpenCL_LIBRARY}
    ${OpenCV_LIBS}
    )
configure_file(kernelheader.cl ${CMAKE_CURRENT_BINARY_DIR}/kernelheader.cl COPYONLY)
configure_file(conv_kernels.cl ${CMAKE_CURRENT_BINARY_DIR}/conv_kernels.cl COPYONLY)
configure_file(fcnn_kernels.cl ${CMAKE_CURRENT_BINARY_DIR}/fcnn_kernels.cl COPYONLY)
