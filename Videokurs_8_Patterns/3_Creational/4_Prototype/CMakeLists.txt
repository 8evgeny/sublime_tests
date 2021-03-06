cmake_minimum_required(VERSION 3.5)

project(Creational_Prototype)

#set (Boost_NO_SYSTEM_PATHS ON)
#set (Boost_USE_MULTITHREADED ON)
#set (Boost_USE_STATIC_LIBS ON)
#set (Boost_USE_STATIC_RUNTIME OFF)
#set (BOOST_ALL_DYN_LINK OFF)

find_package (Boost REQUIRED COMPONENTS  serialization)

add_executable(${PROJECT_NAME}_Prototype  Prototype.cpp)
add_executable(${PROJECT_NAME}_Serialization  Serialization.cpp)


set_target_properties(${PROJECT_NAME}_Prototype  PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
        )
set_target_properties(${PROJECT_NAME}_Serialization  PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
        )

    if (Boost_FOUND)
        message("cmake message-" ${PROJECT_NAME}_Serialization " boost include DIR: " ${Boost_INCLUDE_DIR})
        include_directories (SYSTEM ${Boost_INCLUDE_DIR})
    endif ()

    target_link_libraries(
        ${PROJECT_NAME}_Serialization
        ${Boost_LIBRARIES}
        )
