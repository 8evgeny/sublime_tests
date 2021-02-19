cmake_minimum_required(VERSION 3.5)

project(SE_test LANGUAGES CXX)
file(GLOB src src/* include/*)

SET(MYCOMPILE_FLAGS "-g -Wall -fPIC")
set(CMAKE_C_FLAGS ${MYCOMPILE_FLAGS})

add_library(eph ${src} )
target_include_directories(eph PUBLIC include)

set_target_properties(eph PROPERTIES LINKER_LANGUAGE CXX)

add_executable(swemini
    ${src}
    se.cpp
    )
target_include_directories(swemini PUBLIC eph)
target_include_directories(swemini PUBLIC include)
target_link_libraries(swemini
eph
-lm
-ldl
  )


set (CMAKE_LINKER_FLAGS "-leph -lm -ldl" )
