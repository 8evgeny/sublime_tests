cmake_minimum_required(VERSION 3.5)

project(poko_md5)
#add_definitions("-std=c++11")

#include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
include(${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(${PROJECT_NAME} md5.cpp)

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

