set(CMAKE_CXX_STANDARD 17)
set(name async3)
project(concurrency_${name})

add_executable(${PROJECT_NAME} ${name}.cpp)
target_link_libraries(${PROJECT_NAME}
    pthread
    )


