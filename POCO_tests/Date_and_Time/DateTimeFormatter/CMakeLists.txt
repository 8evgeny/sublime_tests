cmake_minimum_required(VERSION 3.5)

project(DateTimeFormatter)

include(${CMAKE_SOURCE_DIR}/Date_and_Time/${PROJECT_NAME}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(DateTime_${PROJECT_NAME} main.cpp)

set_target_properties(
    DateTime_${PROJECT_NAME}
    PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
    )
target_link_libraries(DateTime_${PROJECT_NAME}
    ${CONAN_LIBS}
    )

