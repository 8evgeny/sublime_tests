cmake_minimum_required(VERSION 3.5)

project(SE_test LANGUAGES CXX)

file(GLOB
    src
    src_cpp/*
    include/*
    )

SET(MYCOMPILE_FLAGS "-g -Wall -fPIC")
set(CMAKE_C_FLAGS ${MYCOMPILE_FLAGS})

add_executable(mini ${src} se.cpp )
add_executable(test ${src} swetest.cpp )

target_include_directories(mini PUBLIC include)
target_include_directories(test PUBLIC include)

target_link_libraries(mini
-lm
-ldl
  )
target_link_libraries(test
-lm
-ldl
  )
set_target_properties(mini test PROPERTIES LINKER_LANGUAGE CXX)

set (CMAKE_LINKER_FLAGS "-leph -lm -ldl" )
