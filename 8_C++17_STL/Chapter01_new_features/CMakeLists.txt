set(CMAKE_CXX_STANDARD 17)

project(1_new_features)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

file (GLOB src *)

add_executable(${PROJECT_NAME}_1_structured_bindings 1_structured_bindings.cpp)
add_executable(${PROJECT_NAME}_2_Limiting_scope_variables_in_if_and_switch_expressions 2_Limiting_scope_variables_in_if_and_switch_expressions.cpp)

add_executable(${PROJECT_NAME}_4_template_class_type_deduction 4_template_class_type_deduction.cpp)
add_executable(${PROJECT_NAME}_5_if_constexpr 5_if_constexpr.cpp)
add_executable(${PROJECT_NAME}_6_inline_variable 6_inline_variable.cpp)
add_executable(${PROJECT_NAME}_7_fold_expressions 7_fold_expressions.cpp)



