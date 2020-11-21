set(CMAKE_CXX_STANDARD 17)

project(deduce_aliastemplate)

FILE (GLOB src_file *.cpp *.hpp)
ADD_EXECUTABLE(${PROJECT_NAME} ${src_file} )



