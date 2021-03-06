cmake_minimum_required(VERSION 3.5)

project(Behavioral-cor-memento_Mediator)

add_executable(${PROJECT_NAME}_chat
    chat.cpp
    ChatRoom.cpp
    Person.cpp
    )
add_executable(${PROJECT_NAME}_mediator  mediator.cpp)

set_target_properties(${PROJECT_NAME}_chat  PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
        )
set_target_properties(${PROJECT_NAME}_mediator  PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
        )
