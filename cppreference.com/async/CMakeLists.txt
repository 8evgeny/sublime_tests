cmake_minimum_required(VERSION 3.5)

project(async)

add_executable(${PROJECT_NAME} async.cpp)
find_library(pthread REQUIRED_FILES)

set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
    )
target_link_libraries(${PROJECT_NAME}
    pthread
    )

