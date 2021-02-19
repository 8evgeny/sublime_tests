cmake_minimum_required(VERSION 3.5)

set (name se)
project(${name} LANGUAGES CXX)
find_library(eph ../SE_build_lib/build/)
add_executable(${PROJECT_NAME}
        se.cpp
    )
target_include_directories(${PROJECT_NAME} PUBLIC eph)
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_link_libraries(${PROJECT_NAME}
-eph
-lm
-ldl
  )
set (CMAKE_LINKER_FLAGS "-leph -lm -ldl" )
