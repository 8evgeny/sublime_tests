cmake_minimum_required(VERSION 3.5)
project(19_thread)

set(CMAKE_CXX_STANDARD 14)

find_package(Threads)

add_executable(${PROJECT_NAME}_thread thread.cpp)

set_target_properties(${PROJECT_NAME}_thread PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED OFF
        COMPILE_OPTIONS "-fsanitize=thread"
        LINK_OPTIONS "-fsanitize=thread"
        )

target_link_libraries(${PROJECT_NAME}_thread
  ${CMAKE_THREAD_LIBS_INIT}
  )

add_executable(${PROJECT_NAME}_static static.cpp)
add_executable(${PROJECT_NAME}_volatile volatile.cpp)
