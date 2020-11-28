cmake_minimum_required(VERSION 3.5)

project(cpp14_3)

add_executable(4_assert assert.cpp)

add_executable(4_move move.cpp)

add_executable(4_literal literal.cpp)

add_executable(4_using using.cpp)

add_executable(4_nullptr nullptr.cpp)

add_executable(4_enum enum.cpp)

add_executable(4_constexpr constexpr.cpp)

add_executable(4_class class.cpp)

add_executable(4_ctor ctor.cpp)

add_executable(4_brace brace.cpp)

add_executable(4_for for.cpp)

add_executable(4_constexpr_ninja constexpr_ninja.cpp)

set_target_properties(4_assert 4_move 4_literal 4_using 4_nullptr 4_enum 4_constexpr 4_class 4_ctor 4_brace 4_for PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
        )
