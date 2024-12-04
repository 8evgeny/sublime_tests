project(handle_message)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20" )

add_executable(${PROJECT_NAME}
    main.cpp
    handle_message.cpp
    handle_message.hpp
    )

