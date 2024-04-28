cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 14)
project(300)
set (OpenCV_DIR /home/evg/opencv/build)
add_executable(1_showImage 1_showImage.cpp)
add_executable(${PROJECT_NAME}_test test.cpp)

find_package( OpenCV REQUIRED )
#find_package(glm REQUIRED)

include_directories(
    ${OpenCV_INCLUDE_DIRS}
#    glm::glm
    )

target_link_libraries( 1_showImage  ${OpenCV_LIBS} )
target_link_libraries( ${PROJECT_NAME}_test  ${OpenCV_LIBS} )
