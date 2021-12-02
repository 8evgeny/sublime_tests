cmake_minimum_required(VERSION 3.5)

project(conan_poko_timer)
#add_definitions("-std=c++11")

#include(${CMAKE_SOURCE_DIR}/conanbuildinfo.cmake)
message ("CMAKE_SOURCE_DIR ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}")

include(${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(${PROJECT_NAME} timer.cpp)

set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
    )
target_link_libraries(${PROJECT_NAME}
    ${CONAN_LIBS}
    )

