cmake_minimum_required(VERSION 3.5)

project(Structural-facade-proxy_Facade)

add_executable(${PROJECT_NAME} Bloom.cpp)

set_target_properties(${PROJECT_NAME}  PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
        )

