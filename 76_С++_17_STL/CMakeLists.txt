cmake_minimum_required(VERSION 3.15)
#set(CMAKE_CXX_STANDARD 17)
project(76_C++_17_STL)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -pthread -fcoroutines")

add_executable(_1  Chapter01/examples-ch1.cc)
add_executable(_2  Chapter02/examples-ch2.cc)
#add_executable(_3  Chapter03/examples-ch3.cc)
#add_executable(_4  Chapter04/examples-ch4.cc)
#Не завершено
