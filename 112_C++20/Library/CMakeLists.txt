set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -pthread -fcoroutines -fmodules-ts")

add_executable(Library_1_bindFront  bindFront.cpp)
add_executable(Library_2_bit  bit.cpp)
