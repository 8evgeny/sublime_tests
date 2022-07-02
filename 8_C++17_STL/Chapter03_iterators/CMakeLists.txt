set(CMAKE_CXX_STANDARD 17)

project(3_iterators)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

file (GLOB src *)

add_executable(${PROJECT_NAME}_1_making_iterators_stl_compatible 1_making_iterators_stl_compatible.cpp)
add_executable(${PROJECT_NAME}_2_own_iterable_range 2_own_iterable_range.cpp)

add_executable(${PROJECT_NAME}_algorithms_in_iterators algorithms_in_iterators.cpp)
add_executable(${PROJECT_NAME}_checked_iterator checked_iterator.cpp)
add_executable(${PROJECT_NAME}_iterator_sentinel iterator_sentinel.cpp)
add_executable(${PROJECT_NAME}_iterator_wrapper iterator_wrapper.cpp)
add_executable(${PROJECT_NAME}_reverse_iterators reverse_iterators.cpp)
add_executable(${PROJECT_NAME}_zip_iterator zip_iterator.cpp)


