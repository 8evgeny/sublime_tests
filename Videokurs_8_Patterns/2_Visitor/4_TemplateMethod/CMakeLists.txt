cmake_minimum_required(VERSION 3.5)

project(Visitor_template_method)

add_executable(${PROJECT_NAME}  template_method.cpp)


set_target_properties(${PROJECT_NAME}  PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
        )
