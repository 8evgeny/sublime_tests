cmake_minimum_required(VERSION 3.5)

set (name C++17)
project(${name} LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME}_1 filesystem_library)
target_link_libraries(${PROJECT_NAME}_1
    -lstdc++fs
    )


