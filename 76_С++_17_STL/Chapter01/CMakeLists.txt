set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -pthread -fcoroutines")

add_executable(_1  examples-ch1.cc)

