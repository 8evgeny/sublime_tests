cmake_minimum_required(VERSION 3.5)

project(Behavioral-cor-memento_Overmath)

file(GLOB src Overmath/*)
file(GLOB src2 Overmath.Notepad/*)
add_executable(${PROJECT_NAME}_Overmath  ${src})
#add_executable(${PROJECT_NAME}_Overmath_Notepad  ${src2})

set_target_properties(${PROJECT_NAME}_Overmath  PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
        )
#set_target_properties(${PROJECT_NAME}_Overmath_Notepad  PROPERTIES
#         CXX_STANDARD 14
#         CXX_STANDARD_REQUIRED ON
#         COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
#         )
