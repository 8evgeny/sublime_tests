cmake_minimum_required(VERSION 3.5)
project(huffman)

add_executable(${PROJECT_NAME}
    coding.cpp
    decoding.cpp
    main.cpp
    )

find_package (Boost REQUIRED COMPONENTS
    system
    filesystem
    program_options
    )

set_target_properties(${PROJECT_NAME} PROPERTIES
            CXX_STANDARD 14
            CXX_EXTENSIONS ON
            )


#if (Boost_FOUND)
#    message("cmake message-" ${PROJECT_NAME} " boost include DIR: " ${Boost_INCLUDE_DIR})
#    include_directories (SYSTEM ${Boost_INCLUDE_DIR})
#endif ()
#target_compile_features(${PROJECT_NAME}_coding PRIVATE cxx_std_17)
target_link_libraries(
    ${PROJECT_NAME}
    ${Boost_LIBRARIES}
     )

