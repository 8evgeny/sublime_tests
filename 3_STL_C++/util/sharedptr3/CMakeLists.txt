set(CMAKE_CXX_STANDARD 17)
set(name sharedptr3)
project(util_${name})

ADD_EXECUTABLE(${PROJECT_NAME} ${name}.cpp)
target_link_libraries(${PROJECT_NAME}
rt
)


