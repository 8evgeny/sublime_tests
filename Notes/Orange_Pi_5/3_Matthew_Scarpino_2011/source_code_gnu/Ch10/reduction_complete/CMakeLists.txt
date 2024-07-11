add_executable(10_reduction_complete reduction_complete.c)
target_link_libraries(10_reduction_complete ${OpenCL_LIBRARY})
configure_file(reduction_complete.cl ${CMAKE_CURRENT_BINARY_DIR}/reduction_complete.cl COPYONLY)

