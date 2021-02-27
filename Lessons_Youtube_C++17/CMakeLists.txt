cmake_minimum_required(VERSION 3.5)

set (name C++17)
project(${name} LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME}_1_filesystem_library filesystem_library.cpp)
target_link_libraries(${PROJECT_NAME}_1_filesystem_library
    -lstdc++fs
    )
add_executable(${PROJECT_NAME}_2_initializations initializations.cpp)
add_executable(${PROJECT_NAME}_3_fold_expression fold_expression.cpp)
