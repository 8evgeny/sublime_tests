cmake_minimum_required(VERSION 3.5)

project(mutex)

add_executable(${PROJECT_NAME} mutex.cpp)
add_executable(${PROJECT_NAME}_try_lock mutex_try_lock.cpp)
find_library(pthread REQUIRED_FILES)

set_target_properties(
    ${PROJECT_NAME}
    ${PROJECT_NAME}_try_lock
    PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
    )
target_link_libraries(${PROJECT_NAME}
    pthread
    )
target_link_libraries(${PROJECT_NAME}_try_lock
    pthread
    )
