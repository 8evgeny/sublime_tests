cmake_minimum_required(VERSION 3.5)

project(SE_build_lib LANGUAGES C)
file(GLOB src src/* include/*)

SET(MYCOMPILE_FLAGS "-g -Wall -fPIC")
set(CMAKE_C_FLAGS ${MYCOMPILE_FLAGS})

add_library(eph ${src} )
target_include_directories(eph PUBLIC include)

set_target_properties(eph PROPERTIES LINKER_LANGUAGE C)

#Не собирается - исследовать MakeFile
add_executable(test
    ${src}
    test.c
    )
target_include_directories(test PUBLIC eph)
target_include_directories(test PUBLIC include)
target_link_libraries(test
eph
-lm
-ldl
  )

add_executable(swemini
    ${src}
    swemini.c
    )
target_include_directories(swemini PUBLIC eph)
target_include_directories(swemini PUBLIC include)
target_link_libraries(swemini
eph
-lm
-ldl
  )


set (CMAKE_LINKER_FLAGS "-leph -lm -ldl" )
