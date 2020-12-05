cmake_minimum_required(VERSION 3.5)

project(gof_3)

add_executable(13_chain_of_responsibility chain_of_responsibility.cpp)
add_executable(13_command command.cpp)
add_executable(13_interpreter interpreter.cpp)
add_executable(13_iterator iterator.cpp)
add_executable(13_mediator mediator.cpp)
add_executable(13_memento memento.cpp)

set_target_properties(13_chain_of_responsibility 13_command 13_interpreter 13_iterator 13_mediator 13_memento PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
        )
