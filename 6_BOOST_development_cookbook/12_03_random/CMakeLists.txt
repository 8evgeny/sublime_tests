project(12_03_random)

include(${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(${PROJECT_NAME} main.cpp)
find_package (Boost REQUIRED COMPONENTS  random )
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
