set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -pthread -fcoroutines")
include_directories("/usr/local/include/fmt/")
find_package(fmt)
add_executable(Ex4_01  Ex4_01.cpp)
add_executable(Ex4_01A  Ex4_01A.cpp)
target_link_libraries(Ex4_01A fmt::fmt)
add_executable(Ex4_02  Ex4_02.cpp)
target_link_libraries(Ex4_02 fmt::fmt)
add_executable(Ex4_02A  Ex4_02A.cpp)
target_link_libraries(Ex4_02A fmt::fmt)
add_executable(Ex4_03  Ex4_03.cpp)
add_executable(Ex4_04  Ex4_04.cpp)
add_executable(Ex4_04A  Ex4_04A.cpp)
add_executable(Ex4_05  Ex4_05.cpp)
add_executable(Ex4_06  Ex4_06.cpp)
add_executable(Ex4_07  Ex4_07.cpp)
target_link_libraries(Ex4_07 fmt::fmt)
add_executable(Ex4_08  Ex4_08.cpp)
add_executable(Ex4_09  Ex4_09.cpp)
add_executable(Ex4_09A  Ex4_09A.cpp)
