cmake_minimum_required(VERSION 3.5)

project(1_project LANGUAGES C)

add_executable(1_project main.c)

install(TARGETS 1_project
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
