#Так не работает
set(CMAKE_PREFIX_PATH "/home/evg/Qt6_4/6.4.0/gcc_64")
qt_examples_build_begin(EXTERNAL_BUILD)
add_subdirectory(wayland)
qt_examples_build_end()

cmake_minimum_required(VERSION 3.16)
project(Examples_6 LANGUAGES CXX)


#add_subdirectory(widgets)
