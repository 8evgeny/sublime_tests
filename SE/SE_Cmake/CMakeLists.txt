cmake_minimum_required(VERSION 3.5)

set (name se)
project(${name} LANGUAGES C)
file(GLOB src src/* include/*)
SET(MYCOMPILE_FLAGS "-g -Wall -fPIC")

set(CMAKE_C_FLAGS ${MYCOMPILE_FLAGS})

add_definitions(${MYCOMPILE_FLAGS})



add_library(eph ${src})
target_include_directories(eph PUBLIC include)
set_target_properties(eph PROPERTIES LINKER_LANGUAGE C)
target_include_directories(eph PUBLIC eph)
add_executable(${PROJECT_NAME}
    src/${name}.cpp
    ${src}
    )
target_include_directories(${PROJECT_NAME} PUBLIC eph)
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_link_libraries(${PROJECT_NAME}
eph
-lm
-ldl
  )
set (CMAKE_LINKER_FLAGS "-leph -lm -ldl" )
