cmake_minimum_required(VERSION 3.5)

project(1_Behavioral)

file(GLOB src Overmath/*)
file(GLOB src2 Overmath_Notepad/*)
add_executable(${PROJECT_NAME}_3_Overmath  ${src})
add_executable(${PROJECT_NAME}_3_Overmath_Notepad  ${src2})


