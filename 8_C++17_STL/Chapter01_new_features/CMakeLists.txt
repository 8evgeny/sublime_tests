set(CMAKE_CXX_STANDARD 17)

project(1_new_features)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

file (GLOB src *)

add_executable(${PROJECT_NAME}_1_structured_bindings 1_structured_bindings.cpp)
add_executable(${PROJECT_NAME}_2_Limiting_scope_variables_in_if_and_switch_expressions 2_Limiting_scope_variables_in_if_and_switch_expressions.cpp)
#add_executable(${PROJECT_NAME}_concatenation concatenation.cpp)
#add_executable(${PROJECT_NAME}_functions_on_the_run functions_on_the_run.cpp)
#add_executable(${PROJECT_NAME}_multicaller multicaller.cpp)
#add_executable(${PROJECT_NAME}_std_function std_function.cpp)
#add_executable(${PROJECT_NAME}_transform_if transform_if.cpp)


