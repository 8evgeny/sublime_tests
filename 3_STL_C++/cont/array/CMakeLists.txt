set(CMAKE_CXX_STANDARD 17)
set(name array)
project(cont_${name})

add_executable(${PROJECT_NAME} ${name}1.cpp)
add_executable(${PROJECT_NAME}cstyle cstyle${name}1.cpp)
add_executable(${PROJECT_NAME}ctyleold cstyle${name}1old.cpp)


