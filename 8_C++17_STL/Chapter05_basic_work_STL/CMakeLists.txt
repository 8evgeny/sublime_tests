set(CMAKE_CXX_STANDARD 17)

project(5_basic_work_STL)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

file (GLOB src *)

add_executable(${PROJECT_NAME}_copying_items copying_items.cpp)
add_executable(${PROJECT_NAME}_dictionary_merge dictionary_merge.cpp)
add_executable(${PROJECT_NAME}_finding_items finding_items.cpp)
add_executable(${PROJECT_NAME}_input_permutations input_permutations.cpp)

#add_executable(${PROJECT_NAME}_pattern_search_string pattern_search_string.cpp)  #Не собирается

add_executable(${PROJECT_NAME}_reducing_range_in_vector reducing_range_in_vector.cpp)
add_executable(${PROJECT_NAME}_removing_items_from_containers removing_items_from_containers.cpp)
add_executable(${PROJECT_NAME}_sampling_vectors sampling_vectors.cpp)
add_executable(${PROJECT_NAME}_sorting_containers sorting_containers.cpp)
add_executable(${PROJECT_NAME}_transforming_items_in_containers transforming_items_in_containers.cpp)
