cmake_minimum_required(VERSION 3.2)

project(gof_4)

add_executable(14_observer observer.cpp)

add_executable(14_state state.cpp)

add_executable(14_strategy strategy.cpp)

add_executable(14_template_method template_method.cpp)

add_executable(14_visitor visitor.cpp)

set_target_properties(14_observer 14_state 14_strategy 14_template_method 14_visitor PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
)
