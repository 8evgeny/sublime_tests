set(CMAKE_CXX_STANDARD 17)
set(name forwardlist)
project(cont_${name})

add_executable(${PROJECT_NAME} ${name}1.cpp)
add_executable(${PROJECT_NAME}_find ${name}find1.cpp)
add_executable(${PROJECT_NAME}_splice ${name}splice1.cpp)



