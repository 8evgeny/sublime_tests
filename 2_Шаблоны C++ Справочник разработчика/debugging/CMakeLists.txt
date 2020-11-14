set(CMAKE_CXX_STANDARD 17)

project(debugging)

FILE (GLOB src_file *.cpp *.hpp)
ADD_EXECUTABLE(${PROJECT_NAME} ${src_file} )



