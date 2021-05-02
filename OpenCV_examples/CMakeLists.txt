cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 14)
project(OpenCV_examples)

add_executable(${PROJECT_NAME}1 1.cpp)
add_executable(${PROJECT_NAME}2 2.cpp)
add_executable(${PROJECT_NAME}3 3.cpp)
add_executable(${PROJECT_NAME}4 4.cpp)

find_package( OpenCV REQUIRED )
find_package(glm REQUIRED)

include_directories(
    ${OpenCV_INCLUDE_DIRS}
    glm::glm
    )

target_link_libraries( ${PROJECT_NAME}1  ${OpenCV_LIBS} )
target_link_libraries( ${PROJECT_NAME}2  ${OpenCV_LIBS} )
target_link_libraries( ${PROJECT_NAME}3  ${OpenCV_LIBS} )
target_link_libraries( ${PROJECT_NAME}4  ${OpenCV_LIBS} )
