set(CMAKE_CXX_STANDARD 17)
set(name utils)
project(cont_${name})

add_executable(${PROJECT_NAME}_refsem refsem1.cpp)
add_executable(${PROJECT_NAME}_refwrap refwrap1.cpp)
add_executable(${PROJECT_NAME}_unordinspect unordinspect1.cpp)


