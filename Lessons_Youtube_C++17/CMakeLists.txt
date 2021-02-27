cmake_minimum_required(VERSION 3.5)

set (name C++17)
project(${name} LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME}_1_initializations initializations.cpp)
add_executable(${PROJECT_NAME}_2_fold_expression fold_expression.cpp)
add_executable(${PROJECT_NAME}_3_filesystem_library filesystem_library.cpp)
target_link_libraries(${PROJECT_NAME}_3_filesystem_library
    -lstdc++fs
    )
add_executable(${PROJECT_NAME}_4_any_optional_variant any_optional_variant.cpp)
add_executable(${PROJECT_NAME}_5_fallthrough fallthrough.cpp)
add_executable(${PROJECT_NAME}_6_nodiscard nodiscard.cpp)
add_executable(${PROJECT_NAME}_7_mayble_unused mayble_unused.cpp)
add_executable(${PROJECT_NAME}_8_non_type_tmpl_param_auto non_type_tmpl_param_auto.cpp)
add_executable(${PROJECT_NAME}_9_cls_tmp_arg_deduction cls_tmp_arg_deduction.cpp)
add_executable(${PROJECT_NAME}_10_decomposing decomposing.cpp)
add_executable(${PROJECT_NAME}_11_tuple_apply tuple_apply.cpp)
