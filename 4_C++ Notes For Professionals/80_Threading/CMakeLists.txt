cmake_minimum_required(VERSION 3.5)

set (name threads)
set (chapter 80)
project(${chapter}_${name} LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME}_1 ${name}1.cpp)
target_link_libraries(${PROJECT_NAME}_1 pthread )
add_executable(${PROJECT_NAME}_2 ${name}2.cpp)
target_link_libraries(${PROJECT_NAME}_2 pthread )
add_executable(${PROJECT_NAME}_3 ${name}3.cpp)
target_link_libraries(${PROJECT_NAME}_3 pthread )
add_executable(${PROJECT_NAME}_4 ${name}4.cpp)
target_link_libraries(${PROJECT_NAME}_4 pthread )
add_executable(${PROJECT_NAME}_5 ${name}5.cpp)
target_link_libraries(${PROJECT_NAME}_5 pthread )
add_executable(${PROJECT_NAME}_async ${name}_async.cpp)
target_link_libraries(${PROJECT_NAME}_async pthread )
add_executable(${PROJECT_NAME}_basic_synchronization ${name}_basic_synchronization.cpp)
target_link_libraries(${PROJECT_NAME}_basic_synchronization pthread )
add_executable(${PROJECT_NAME}_simple_thread_pool ${name}_simple_thread_pool.cpp)
target_link_libraries(${PROJECT_NAME}_simple_thread_pool pthread )
add_executable(${PROJECT_NAME}_always_joined ${name}_always_joined.cpp)
target_link_libraries(${PROJECT_NAME}_always_joined pthread )
add_executable(${PROJECT_NAME}_current_thread_operations ${name}_current_thread_operations.cpp)
target_link_libraries(${PROJECT_NAME}_current_thread_operations pthread )
add_executable(${PROJECT_NAME}_condition_variables ${name}_condition_variables.cpp)
target_link_libraries(${PROJECT_NAME}_condition_variables pthread )
