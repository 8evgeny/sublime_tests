set(CMAKE_CXX_STANDARD 17)

project(deduce_initlist)

FILE (GLOB src_file *.cpp *.hpp)
ADD_EXECUTABLE(${PROJECT_NAME} ${src_file} )



