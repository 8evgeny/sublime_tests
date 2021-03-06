cmake_minimum_required(VERSION 3.5)

project(cpp17_1)

add_executable(5_attributes attributes.cpp)
add_executable(5_auto_template auto_template.cpp)
add_executable(5_deduction deduction.cpp)
add_executable(5_lambda lambda.cpp)
add_executable(5_noexcept noexcept.cpp)
add_executable(5_static_assert static_assert.cpp)
add_executable(5_trigraph trigraph.cpp)

set_target_properties(5_attributes 5_auto_template 5_deduction 5_lambda 5_noexcept 5_static_assert PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
        COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
        )


set_target_properties(5_trigraph PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
        COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
        )
