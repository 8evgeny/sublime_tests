cmake_minimum_required(VERSION 3.5)

project(test LANGUAGES CXX)

file(GLOB
    src
    src_cpp/*
    include/*
    )

find_package (Boost REQUIRED COMPONENTS
    system
    filesystem
    program_options
    )

#if (Boost_FOUND)
#    message("cmake message-" ${PROJECT_NAME} " boost include DIR: " ${Boost_INCLUDE_DIR})
#    include_directories (SYSTEM ${Boost_INCLUDE_DIR})
#endif ()
#target_compile_features(${PROJECT_NAME}_coding PRIVATE cxx_std_17)





SET(MYCOMPILE_FLAGS "-g -Wall -fPIC")
set(CMAKE_C_FLAGS ${MYCOMPILE_FLAGS})

add_executable(mini ${src} se.cpp )
add_executable(test ${src} main.cpp test.cpp functions.cpp)

target_include_directories(mini PUBLIC include)
target_include_directories(${PROJECT_NAME} PUBLIC include)

target_link_libraries(mini
-lm
-ldl
  )
target_link_libraries(${PROJECT_NAME}
-lm
-ldl
${Boost_LIBRARIES}
pthread
  )
set_target_properties(mini PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(${PROJECT_NAME} PROPERTIES
            CXX_STANDARD 14
            CXX_EXTENSIONS ON
            )
set (CMAKE_LINKER_FLAGS "-leph -lm -ldl" )









