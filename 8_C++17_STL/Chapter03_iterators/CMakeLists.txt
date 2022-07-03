set(CMAKE_CXX_STANDARD 17)

project(3_iterators)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

file (GLOB src *)

add_executable(${PROJECT_NAME}_1_making_iterators_stl_compatible 1_making_iterators_stl_compatible.cpp)
add_executable(${PROJECT_NAME}_2_own_iterable_range 2_own_iterable_range.cpp)
add_executable(${PROJECT_NAME}_3_iterator_wrapper 3_iterator_wrapper.cpp)
add_executable(${PROJECT_NAME}_4_algorithms_in_iterators 4_algorithms_in_iterators.cpp)
add_executable(${PROJECT_NAME}_5_reverse_iterators 5_reverse_iterators.cpp)
add_executable(${PROJECT_NAME}_6_iterator_sentinel 6_iterator_sentinel.cpp)

add_definitions(-D_GLIBCXX_DEBUG) #макрос препроцессора, который активизирует много функций для проверки достоверности STL.
add_executable(${PROJECT_NAME}_7_checked_iterator 7_checked_iterator.cpp)

add_executable(${PROJECT_NAME}_8_zip_iterator 8_zip_iterator.cpp)


