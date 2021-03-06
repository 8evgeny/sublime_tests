cmake_minimum_required(VERSION 3.5)

project(Structural-adapter-decorator_Decorator)

#find_package (Boost REQUIRED COMPONENTS  serialization)

add_executable(${PROJECT_NAME} decorator.cpp)

set_target_properties(${PROJECT_NAME}  PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
        )

#if (Boost_FOUND)
#    message("cmake message-" ${PROJECT_NAME}_Serialization " boost include DIR: " ${Boost_INCLUDE_DIR})
#    include_directories (SYSTEM ${Boost_INCLUDE_DIR})
#endif ()

#target_link_libraries(
#   ${PROJECT_NAME}
#   ${Boost_LIBRARIES}
#   )
