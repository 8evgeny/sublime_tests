cmake_minimum_required(VERSION 3.5)

project(Creational_Preliminaries)

add_executable(${PROJECT_NAME}_LSP  LSP.cpp)
add_executable(${PROJECT_NAME}_OCP  OCP.cpp)
add_executable(${PROJECT_NAME}_BoostDI  BoostDI.cpp)

set_target_properties(${PROJECT_NAME}_LSP  PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
        )
set_target_properties(${PROJECT_NAME}_OCP  PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
        )
set_target_properties(${PROJECT_NAME}_BoostDI  PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
        )
