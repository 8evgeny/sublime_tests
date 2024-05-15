cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 14)
project(301)
set (OpenCV_DIR /home/evg/opencv/build)

find_package( OpenCV REQUIRED )
#find_package(Qt5Widgets REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(1_showImage 1_showImage.cpp)
add_executable(2_3_showVideo 2_3_showVideo.cpp)
add_executable(2_4_showVideo 2_4_showVideo.cpp)
add_executable(2_5_blur 2_5_blur.cpp)

target_link_libraries( 1_showImage  ${OpenCV_LIBS} )
target_link_libraries( 2_3_showVideo  ${OpenCV_LIBS} )
target_link_libraries( 2_4_showVideo  ${OpenCV_LIBS} )
target_link_libraries( 2_5_blur  ${OpenCV_LIBS} )
