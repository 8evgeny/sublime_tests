project(12_05_testing)

include(${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/conanbuildinfo.cmake)
conan_basic_setup()
find_package (Boost REQUIRED COMPONENTS  unit_test_framework)
add_executable(${PROJECT_NAME} main.cpp)

set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
    )
target_link_libraries(${PROJECT_NAME}
    ${CONAN_LIBS}
    ${Boost_LIBRARIES}
    )
