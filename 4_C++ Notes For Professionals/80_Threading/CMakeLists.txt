cmake_minimum_required(VERSION 3.5)

set (name threads)
project(${name} LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME}_1 ${name}1.cpp)
target_link_libraries(${PROJECT_NAME}_1 pthread )
add_executable(${PROJECT_NAME}_2 ${name}2.cpp)
target_link_libraries(${PROJECT_NAME}_2 pthread )
add_executable(${PROJECT_NAME}_3 ${name}3.cpp)
target_link_libraries(${PROJECT_NAME}_3 pthread )
add_executable(${PROJECT_NAME}_4 ${name}4.cpp)
target_link_libraries(${PROJECT_NAME}_4 pthread )

#add_executable(${PROJECT_NAME}_5 ${name}5.cpp)     //не собирается
#target_link_libraries(${PROJECT_NAME}_5 pthread )


