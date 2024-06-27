add_executable(2_queue_kernel queue_kernel.c)
target_link_libraries(2_queue_kernel ${OpenCL_LIBRARY} )
configure_file(blank.cl ${CMAKE_CURRENT_BINARY_DIR}/blank.cl COPYONLY)



