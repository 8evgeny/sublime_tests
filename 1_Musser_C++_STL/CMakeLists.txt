cmake_minimum_required(VERSION 3.05)
set(CMAKE_CXX_STANDARD 17)
project(1_Musser_C++_STL)

add_executable(ex02-01_STL_generic_reverse_algorithm_with_string_and_array ex02-01.cpp)
add_executable(ex02-02_STL_generic_reverse_algorithm_with_vector ex02-02.cpp)
add_executable(ex02-03_STL_generic_reverse_algorithm_with_list ex02-03.cpp)
add_executable(ex02-04_STL_map ex02-04.cpp)
add_executable(ex02-05_generic_find_algorithm_with_array ex02-05.cpp)
add_executable(ex02-06_generic_find_algorithm_with_vector ex02-06.cpp)
add_executable(ex02-07_generic_find_algorithm_with_list ex02-07.cpp)
add_executable(ex02-08_generic_find_algorithm_with_deque ex02-08.cpp)
add_executable(ex02-09_generic_merge_algorithm_with_array_list_deque ex02-09.cpp)
add_executable(ex02-10_generic_merge_algorithm_with_array_list_deque ex02-10.cpp)
add_executable(ex02-11_generic_accumulate_function ex02-11.cpp)
add_executable(ex02-12_generic_accumulate_function ex02-12.cpp)
add_executable(ex02-13_generic_accumulate_function_function_object ex02-13.cpp)
add_executable(ex02-14_generic_accumulate_function_multiplies ex02-14.cpp)
add_executable(ex02-15_generic_accumulate_algorithm_reverse_iterator ex02-15.cpp)

add_executable(ex04-01_generic_find_algorithm_with_input_iterators_associated_with_arrays_lists_iostreams ex04-01.cpp)

add_executable(ex05-01_in-place_generic_sort_algorithm ex05-01.cpp)
add_executable(ex05-02_Using_reverse_copy_copying_version_generic_reverse_algorithm ex05-02.cpp)
add_executable(ex05-03_Using_generic_sort_algorithm_with_a_binary_predicate ex05-03.cpp)
add_executable(ex05-04_generic_find_if_algorithm ex05-04.cpp)
add_executable(ex05-05_generic_adjacent_find_algorithm ex05-05.cpp)
add_executable(ex05-06_generic_count_algorithm ex05-06.cpp)
add_executable(ex05-07_generic_for_each_algorithm ex05-07.cpp)
add_executable(ex05-08_generic_equal_and_mismatch_algorithms ex05-08.cpp)
add_executable(ex05-09_generic_search_algorithm ex05-09.cpp)
add_executable(ex05-10_generic_copy_copy_backward_algorithms ex05-10.cpp)
add_executable(ex05-11_generic_fill_fill_n_algorithms ex05-11.cpp)
add_executable(ex05-12_generic_generate_algorithm ex05-12.cpp)
add_executable(ex05-13_generic_partition_stable_partition_algorithms ex05-13.cpp)
add_executable(ex05-14_random_shuffle_algorithm ex05-14.cpp)
add_executable(ex05-15_generic_remove_algorithm ex05-15.cpp)
add_executable(ex05-16_generic_replace_algorithm ex05-16.cpp)
add_executable(ex05-17_generic_rotate_algorithm ex05-17.cpp)
add_executable(ex05-18_generic_swap_algorithm ex05-18.cpp)
add_executable(ex05-19_generic_swap_ranges_algorithm ex05-19.cpp)
add_executable(ex05-20_generic_transform_algorithm ex05-20.cpp)
add_executable(ex05-21_generic_unique_algorithm ex05-21.cpp)
add_executable(ex05-22_generic_sort_stable_sort_partial_sort_algorithms ex05-22.cpp)
add_executable(ex05-23_generic_nth_element_algorithm ex05-23.cpp)
add_executable(ex05-24_generic_binary_search_algorithms ex05-24.cpp)
add_executable(ex05-25_generic_merge_algorithms ex05-25.cpp)
add_executable(ex05-26_generic_set_operations ex05-26.cpp)
add_executable(ex05-27_generic_heap_operations ex05-27.cpp)
add_executable(ex05-28_generic_min_element_max_element_algorithms ex05-28.cpp)
add_executable(ex05-29_generic_lexicographical_compare_algorithm ex05-29.cpp)
add_executable(ex05-30_generic_permutation_algorithms ex05-30.cpp)
add_executable(ex05-31_generic_accumulate_algorithm ex05-31.cpp)
add_executable(ex05-32_generic_partial_sum_algorithm ex05-32.cpp)
add_executable(ex05-33_generic_adjacent_difference_algorithm ex05-33.cpp)
add_executable(ex05-34_generic_inner_product_algorithm ex05-34.cpp)

add_executable(ex06-01_simplest_vector_constructors ex06-01.cpp)
add_executable(ex06-02_vector_constructors_with_user-defined_type ex06-02.cpp)


add_executable(ex09-01_Illustrating_stack_adaptor ex09-01.cpp)
add_executable(ex09-02_Illustrating_queue_adaptor ex09-02.cpp)
add_executable(ex09-03_Illustrating_priority_queue_adaptor ex09-03.cpp)

add_executable(ex10-01_Illustrating_normal_reverse_iteration ex10-01.cpp)
add_executable(ex10-02_Using_find_with_normal_reverse_iteration ex10-02.cpp)

add_executable(ex11-01_Sort_a_vector_into_ascending_order_of_id_members ex11-01.cpp)
add_executable(ex11-02_Use_adaptor_for_pointers_to_functions ex11-02.cpp)

add_executable(ex12-01_Program_to_find_all_anagrams_of_a_given_word_using_a_dictionary ex12-01.cpp)


add_executable(ex16-01_Demonstrating_a_counting_iterator_class ex16-01.cpp)

add_executable(ex17-01_Combining_STL_components_with_inheritance_and_virtual_functions
    ex17-01.cpp
    shape.cpp
    screen.cpp)

add_executable(ex18-01_Read_TCS_Genealogical_Database_file_and_display_its_tree_structure_using_indentation_with_names ex18-01.cpp)

add_executable(ex19-01_First_attempt_at_timing_the_sort_algorithm ex19-01.cpp)
add_executable(ex19-01a_First_attempt_at_timing_the_sort_algorithm_measuring_the_baseline_time ex19-01a.cpp)
add_executable(ex19-02_Timing_sort_on_random_vectors ex19-02.cpp)
