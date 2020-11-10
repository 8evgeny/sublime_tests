cmake_minimum_required(VERSION 3.5)

project(POCO LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(SOURCE_FILES main.cpp)

set(POCO_PREFIX      "/home/jhon/POCO/cmake-build") # the directory containing "include" and "lib"
set(POCO_INCLUDE_DIR "${POCO_PREFIX}/include")
set(POCO_LIB_DIR     "${POCO_PREFIX}/lib")
set(POCO_LIBS        "${POCO_LIB_DIR}/libPocoNetd"
                     "${POCO_LIB_DIR}/libPocoUtil"
                     "${POCO_LIB_DIR}/libPocoNetd.a"
                     "${POCO_LIB_DIR}/libPocoUtild.a"
                     "${POCO_LIB_DIR}/libPocoJSONd.a"
                     "${POCO_LIB_DIR}/libPocoXMLd.a"
                     "${POCO_LIB_DIR}/libPocoFoundationd.a"
                     "pthread")
add_executable(POCO ${SOURCE_FILES})
target_include_directories(POCO PRIVATE "${POCO_INCLUDE_DIR}")
target_link_libraries(POCO "${POCO_LIBS}")



## define the project
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#set(SOURCE_FILES main.cpp)
#add_executable(Email_Reader ${SOURCE_FILES})


