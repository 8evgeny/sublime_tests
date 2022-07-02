set(CMAKE_CXX_STANDARD 17)

project(4_lambdas)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

file (GLOB src *)
add_executable(${PROJECT_NAME}_1_functions_on_the_run 1_functions_on_the_run.cpp)
add_executable(${PROJECT_NAME}_2_std_function 2_std_function.cpp)
add_executable(${PROJECT_NAME}_3_concatenation 3_concatenation.cpp)
add_executable(${PROJECT_NAME}_4_combine 4_combine.cpp)
add_executable(${PROJECT_NAME}_5_multicaller 5_multicaller.cpp)
add_executable(${PROJECT_NAME}_6_transform_if 6_transform_if.cpp)
add_executable(${PROJECT_NAME}_7_cartesian_product 7_cartesian_product.cpp)



