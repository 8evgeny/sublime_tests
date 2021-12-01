cmake_minimum_required(VERSION 3.5)

project(POCO_1)

set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(SOURCE_FILES main.cpp)
#add_executable(poco ${SOURCE_FILES})
#set(POCO_PREFIX      "/usr/local") # the directory containing "include" and "lib"
#set(POCO_INCLUDE_DIR "${POCO_PREFIX}/include")
#set(POCO_LIB_DIR     "${POCO_PREFIX}/lib")
#set(POCO_LIBS        "${POCO_LIB_DIR}/libPocoNet.so"
#                     "${POCO_LIB_DIR}/libPocoUtil.so"
#                     "${POCO_LIB_DIR}/libPocoFoundation.so"
##                     "${POCO_LIB_DIR}/libPocoNetd.a"
##                     "${POCO_LIB_DIR}/libPocoUtild.a"
##                     "${POCO_LIB_DIR}/libPocoJSONd.a"
##                     "${POCO_LIB_DIR}/libPocoXMLd.a"
#                      "pthread"
#                        )
#message(${POCO_LIBS})

#target_include_directories(poco PRIVATE "${POCO_INCLUDE_DIR}")
#target_link_libraries(poco
#    PUBLIC
#    "${POCO_LIBS}"
#    )

cmake_minimum_required(VERSION 3.5)

project(conan_poko_net)
#add_definitions("-std=c++11")

#include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
include(conanbuildinfo.cmake)
conan_basic_setup()

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
    )

