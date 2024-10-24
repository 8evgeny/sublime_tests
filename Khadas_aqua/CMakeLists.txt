cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)

project(aqua)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(Qt5 REQUIRED COMPONENTS Core)
include_directories(${CMAKE_SOURCE_DIR})
include_directories(${Qt5Widgets_INCLUDE_DIRS} ${Qt5Widgets_LIBRARIES} ${CMAKE_CURRENT_BINARY_DIR} ${Qt5Core_INCLUDE_DIRS} ${Qt5Core_LIBRARIES})
add_executable(${PROJECT_NAME} main.cpp )
#add_executable(time time.cpp)
target_link_libraries(${PROJECT_NAME}
pthread
wiringPi
pthread
rt
m
crypt
Qt5::Core
)
