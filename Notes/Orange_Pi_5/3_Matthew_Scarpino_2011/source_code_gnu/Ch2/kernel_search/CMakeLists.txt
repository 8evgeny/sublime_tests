add_executable(2_kernel_search kernel_search.c)
target_link_libraries(2_kernel_search ${OpenCL_LIBRARY} )
configure_file(test.cl ${CMAKE_CURRENT_BINARY_DIR}/test.cl COPYONLY)


