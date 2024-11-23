set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
    -std=c++20 \
    -pthread \
    -fcoroutines \
    -fmodules-ts" )
#stdlib=libc++/stdlib=libstdc++
add_executable(Arithmetic_bit  bit.cpp)

