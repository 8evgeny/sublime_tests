cmake_minimum_required(VERSION 3.5)

project(SE_test LANGUAGES CXX)

file(GLOB
    src
    src_cpp/*
    include/*
    )

SET(MYCOMPILE_FLAGS "-g -Wall -fPIC")
set(CMAKE_C_FLAGS ${MYCOMPILE_FLAGS})

add_executable(test
    ${src}
    se.cpp
    )
target_include_directories(test PUBLIC include)
target_link_libraries(test
-lm
-ldl
  )

set_target_properties(test PROPERTIES LINKER_LANGUAGE CXX)

set (CMAKE_LINKER_FLAGS "-leph -lm -ldl" )
