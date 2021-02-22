set(CMAKE_CXX_STANDARD 17)
project(72_Parallel_programming_C++)

add_executable(1_1_helloworld listing_1.1.cpp)
target_link_libraries(1_1_helloworld pthread)

add_executable(2_1 listing_2.1.cpp)
target_link_libraries(2_1 pthread)

add_executable(2_2_ожидание_завершения_потока listing_2.2.cpp)
target_link_libraries(2_2_ожидание_завершения_потока pthread)
