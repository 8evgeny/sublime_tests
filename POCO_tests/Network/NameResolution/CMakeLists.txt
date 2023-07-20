cmake_minimum_required(VERSION 3.5)

project(NameResolution)

include(${CMAKE_SOURCE_DIR}/Network/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(Network_${PROJECT_NAME} main.cpp)

set_target_properties(
    Network_${PROJECT_NAME}
    PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
    )
target_link_libraries(Network_${PROJECT_NAME}
    ${CONAN_LIBS}
    )

