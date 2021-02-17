cmake_minimum_required(VERSION 3.5)

set (name se)
project(${name} LANGUAGES CXX)
file(GLOB src src/*)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(eph ${src})
set_target_properties(eph PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(eph PUBLIC eph)
add_executable(${PROJECT_NAME}
    src/${name}.cpp
    ${src}
    )
target_include_directories(${PROJECT_NAME} PUBLIC eph)
target_link_libraries(${PROJECT_NAME}
eph
    )
