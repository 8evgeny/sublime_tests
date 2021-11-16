cmake_minimum_required(VERSION 3.5)

project(1_Behavioral_1_ChainOfResponsibility)

add_executable(${PROJECT_NAME}_broker  cor_broker.cpp)
add_executable(${PROJECT_NAME}_pointer  cor_pointer.cpp)


