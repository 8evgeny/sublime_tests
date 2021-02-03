set(CMAKE_CXX_STANDARD 17)
set(name regex1)
project(regex_${name})

add_executable(${PROJECT_NAME} ${name}.cpp)
target_link_libraries(${PROJECT_NAME}
    pthread
    )


