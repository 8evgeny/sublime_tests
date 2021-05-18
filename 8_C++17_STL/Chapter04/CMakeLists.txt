set(CMAKE_CXX_STANDARD 17)

project(lambdas)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

file (GLOB src *)

add_executable(${PROJECT_NAME}_cartesian_product cartesian_product.cpp)
add_executable(${PROJECT_NAME}_combine combine.cpp)
add_executable(${PROJECT_NAME}_concatenation concatenation.cpp)
add_executable(${PROJECT_NAME}_functions_on_the_run functions_on_the_run.cpp)
add_executable(${PROJECT_NAME}_multicaller multicaller.cpp)
add_executable(${PROJECT_NAME}_std_function std_function.cpp)
add_executable(${PROJECT_NAME}_transform_if transform_if.cpp)


