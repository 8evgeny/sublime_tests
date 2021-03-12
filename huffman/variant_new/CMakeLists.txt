cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 17)
project(huffman)

#add_executable(${PROJECT_NAME}_decoding
#    decoding.cpp
#    )

add_executable(${PROJECT_NAME}_coding
    coding.cpp
    )

find_package (Boost REQUIRED COMPONENTS
    system
    filesystem
    )
#if (Boost_FOUND)
#    message("cmake message-" ${PROJECT_NAME} " boost include DIR: " ${Boost_INCLUDE_DIR})
#    include_directories (SYSTEM ${Boost_INCLUDE_DIR})
#endif ()

target_link_libraries(
    ${PROJECT_NAME}_coding
    ${Boost_LIBRARIES}
     )
