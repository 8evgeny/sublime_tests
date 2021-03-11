cmake_minimum_required(VERSION 3.5)

project(future)

add_executable(${PROJECT_NAME}_promise promise.cpp)
add_executable(${PROJECT_NAME}_packaged_task packaged_task.cpp)
add_executable(${PROJECT_NAME}_packaged_task2 packaged_task2.cpp)
find_library(pthread REQUIRED_FILES)

set_target_properties(
    ${PROJECT_NAME}_promise
    ${PROJECT_NAME}_packaged_task
    ${PROJECT_NAME}_packaged_task2
    PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
    )
target_link_libraries(${PROJECT_NAME}_promise
    pthread
    )
target_link_libraries(${PROJECT_NAME}_packaged_task
    pthread
    )
target_link_libraries(${PROJECT_NAME}_packaged_task2
    pthread
    )
