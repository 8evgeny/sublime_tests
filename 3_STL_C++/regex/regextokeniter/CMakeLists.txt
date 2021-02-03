set(CMAKE_CXX_STANDARD 17)
set(name regextokeniter)
project(regex_${name})

add_executable(${PROJECT_NAME} regextokeniter1.cpp)
target_link_libraries(${PROJECT_NAME}
    pthread
    )


