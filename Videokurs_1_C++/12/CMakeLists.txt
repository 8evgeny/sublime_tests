cmake_minimum_required(VERSION 3.5)

project(gof_2)

add_executable(12_adapter adapter.cpp)
add_executable(12_bridge bridge.cpp)
add_executable(12_composite composite.cpp)
add_executable(12_decorator decorator.cpp)
add_executable(12_facade facade.cpp)
add_executable(12_flyweight flyweight.cpp)
add_executable(12_proxy proxy.cpp)

set_target_properties(12_adapter 12_bridge 12_composite 12_decorator 12_facade 12_flyweight 12_proxy PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
        )
