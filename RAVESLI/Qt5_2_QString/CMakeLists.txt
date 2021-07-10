cmake_minimum_required(VERSION 3.5)

set (name Qt_String)
project(${name} LANGUAGES CXX)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#file (GLOB src *)

find_package(Qt5Core)
add_executable(${PROJECT_NAME}_1 1.cpp )
add_executable(${PROJECT_NAME}_2 2.cpp )
add_executable(${PROJECT_NAME}_3 3.cpp )
add_executable(${PROJECT_NAME}_4 4.cpp )
add_executable(${PROJECT_NAME}_5 5.cpp )
add_executable(${PROJECT_NAME}_6 6.cpp )
add_executable(${PROJECT_NAME}_7 7.cpp )
add_executable(${PROJECT_NAME}_8 8.cpp )
add_executable(${PROJECT_NAME}_9 9.cpp )
add_executable(${PROJECT_NAME}_10 10.cpp )
add_executable(${PROJECT_NAME}_11 11.cpp )
add_executable(${PROJECT_NAME}_12 12.cpp )
#    ${src} )

set_target_properties(${PROJECT_NAME}_1  PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
    )

target_link_libraries(${PROJECT_NAME}_1 Qt5::Core)
target_link_libraries(${PROJECT_NAME}_2 Qt5::Core)
target_link_libraries(${PROJECT_NAME}_3 Qt5::Core)
target_link_libraries(${PROJECT_NAME}_4 Qt5::Core)
target_link_libraries(${PROJECT_NAME}_5 Qt5::Core)
target_link_libraries(${PROJECT_NAME}_6 Qt5::Core)
target_link_libraries(${PROJECT_NAME}_7 Qt5::Core)
target_link_libraries(${PROJECT_NAME}_8 Qt5::Core)
target_link_libraries(${PROJECT_NAME}_9 Qt5::Core)
target_link_libraries(${PROJECT_NAME}_10 Qt5::Core)
target_link_libraries(${PROJECT_NAME}_11 Qt5::Core)
target_link_libraries(${PROJECT_NAME}_12 Qt5::Core)
#Qt${QT_VERSION_MAJOR}::Core)
