cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 14)
project(300)
set (OpenCV_DIR /home/evg/opencv/build)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(1_showImage 1_showImage.cpp)
add_executable(2_videoCapture 2_videoCapture.cpp)
add_executable(3_showUI 3_showUI.cpp)
add_executable(test test.cpp)

target_link_libraries( 1_showImage  ${OpenCV_LIBS} )
target_link_libraries( 2_videoCapture  ${OpenCV_LIBS} )
target_link_libraries( 3_showUI  ${OpenCV_LIBS} )
target_link_libraries( test  ${OpenCV_LIBS} )
