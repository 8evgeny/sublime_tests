cmake_minimum_required(VERSION 3.5)

project(Behavioral-cor-memento_ChainOfResponsibility)

add_executable(${PROJECT_NAME}_broker  cor_broker.cpp)
add_executable(${PROJECT_NAME}_pointer  cor_pointer.cpp)

set_target_properties(${PROJECT_NAME}_broker  PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
        )
set_target_properties(${PROJECT_NAME}_pointer  PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
        )
