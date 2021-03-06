cmake_minimum_required(VERSION 3.5)
project(boost_1)

find_package(Boost COMPONENTS program_options unit_test_framework REQUIRED)

include_directories(${Boost_INCLUDE_DIR})

set(CMAKE_CXX_STANDARD 14)

add_executable(17_bimap bimap.cpp)
add_executable(17_circular_buffer circular_buffer.cpp)
add_executable(17_format format.cpp)
add_executable(17_fusion fusion.cpp)
add_executable(17_multi_index multi_index.cpp)
add_executable(17_program_options program_options.cpp)
add_executable(17_test test.cpp)
add_executable(17_tokenizer tokenizer.cpp)

target_link_libraries(17_program_options
        ${Boost_LIBRARIES}
        )

target_link_libraries(17_test
        ${Boost_LIBRARIES}
        )

set_target_properties(17_test PROPERTIES
        COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
        )
