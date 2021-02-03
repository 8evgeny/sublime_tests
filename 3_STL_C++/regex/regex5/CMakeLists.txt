set(CMAKE_CXX_STANDARD 17)
set(name regex5)
project(regex_${name})

add_executable(${PROJECT_NAME} ${name}.cpp regexexception.hpp)
target_link_libraries(${PROJECT_NAME}
    pthread
    )


