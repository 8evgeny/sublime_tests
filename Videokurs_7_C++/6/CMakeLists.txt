cmake_minimum_required(VERSION 3.5)

project(cpp17_2)

add_executable(6_fold fold.cpp)
set_target_properties(6_fold PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

add_executable(6_filesystem filesystem.cpp)
set_target_properties(6_filesystem PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

add_executable(6_constexpr_if constexpr_if.cpp)
set_target_properties(6_constexpr_if PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

add_executable(6_inline inline.cpp)
set_target_properties(6_inline PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

add_executable(6_initializers initializers.cpp)
set_target_properties(6_initializers PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

add_executable(6_structured_bindings structured_bindings.cpp)
set_target_properties(6_structured_bindings PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

add_executable(6_sv sv.cpp)
set_target_properties(6_sv PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

add_executable(6_evaluation_order evaluation_order.cpp)
set_target_properties(6_evaluation_order PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

add_executable(6_bind bind.cpp)
set_target_properties(6_bind PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
