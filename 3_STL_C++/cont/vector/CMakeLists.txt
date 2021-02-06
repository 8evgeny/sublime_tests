set(CMAKE_CXX_STANDARD 17)
set(name vector)
project(cont_${name})

add_executable(${PROJECT_NAME} ${name}1.cpp)
add_executable(${PROJECT_NAME}_sort sortvec.cpp)



