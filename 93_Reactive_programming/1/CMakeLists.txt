cmake_minimum_required(VERSION 3.5)

project(1)

add_executable(${PROJECT_NAME} 1.cpp)

set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
    )
target_link_libraries(${PROJECT_NAME}
    -L/usr/X11R6/lib
    -lX11
    )

