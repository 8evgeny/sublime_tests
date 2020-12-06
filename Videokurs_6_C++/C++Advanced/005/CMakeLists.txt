cmake_minimum_required(VERSION 2.8)

project(advanced_5)
add_compile_options( -std=c++11 )

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)
add_executable(${PROJECT_NAME} "main.cpp")
set(CMAKE_CXX_FLAGS "-pthread -lpthread")
set(CMAKE_LD_FLAGS "-pthread -lpthread")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lpthread -lm")

#target_link_libraries(${PROJECT_NAME} Threads::Threads)
target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})
#target_link_libraries(${PROJECT_NAME} PUBLIC pthread)
target_link_libraries(${PROJECT_NAME} PUBLIC stdc++)
