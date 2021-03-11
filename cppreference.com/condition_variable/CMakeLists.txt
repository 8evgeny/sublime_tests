cmake_minimum_required(VERSION 3.5)

project(condition_variable)

add_executable(${PROJECT_NAME} condition_variable.cpp)
add_executable(${PROJECT_NAME}2 condition_variable2.cpp)
add_executable(${PROJECT_NAME}_wait condition_variable_wait.cpp)
find_library(pthread REQUIRED_FILES)

set_target_properties(
    ${PROJECT_NAME}
    ${PROJECT_NAME}2
    ${PROJECT_NAME}_wait
    PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
    )
target_link_libraries(${PROJECT_NAME}
    pthread
    )
target_link_libraries(${PROJECT_NAME}2
    pthread
    )
target_link_libraries(${PROJECT_NAME}_wait
    pthread
    )
