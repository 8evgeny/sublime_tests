cmake_minimum_required(VERSION 3.5)

project(Creational_Singleton)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})


add_executable(${PROJECT_NAME}  SingletonTests.cpp)


set_target_properties(${PROJECT_NAME}  PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
        )
target_link_libraries(${PROJECT_NAME}
    ${GTEST_LIBRARY}
    ${GTEST_MAIN_LIBRARY}
    )

#add_test(
#     NAME runUnitTests
#     COMMAND runUnitTests
#     )
