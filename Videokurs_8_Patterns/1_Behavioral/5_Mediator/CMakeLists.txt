cmake_minimum_required(VERSION 3.5)

project(1_Behavioral)

add_executable(${PROJECT_NAME}_5_chat
    chat.cpp
    ChatRoom.cpp
    Person.cpp
    )
add_executable(${PROJECT_NAME}_5_mediator  mediator.cpp)

