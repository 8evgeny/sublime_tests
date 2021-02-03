set(CMAKE_CXX_STANDARD 17)
set(name regexiter)
project(regex_${name})

add_executable(${PROJECT_NAME} regexiter1.cpp)
target_link_libraries(${PROJECT_NAME}
    pthread
    )


