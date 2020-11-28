cmake_minimum_required(VERSION 3.5)

project(gof_1)

add_executable(11_abstract_factory abstract_factory.cpp)
add_executable(11_builder builder.cpp)
add_executable(11_dependency_injection dependency_injection.cpp)
add_executable(11_factory_method factory_method.cpp)
add_executable(11_lazy_initialization lazy_initialization.cpp)
add_executable(11_multiton multiton.cpp)
add_executable(11_object_pool object_pool.cpp)
add_executable(11_prototype prototype.cpp)
add_executable(11_singleton singleton.cpp)

set_target_properties(11_abstract_factory 11_builder 11_dependency_injection 11_factory_method 11_lazy_initialization 11_multiton 11_object_pool 11_prototype 11_singleton PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
    )
