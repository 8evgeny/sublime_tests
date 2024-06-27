add_executable(2_6_Events events.c)
target_link_libraries(2_6_Events ${OPENCL_LIBRARIES} )
configure_file(sample_kernel.cl ${CMAKE_CURRENT_BINARY_DIR}/sample_kernel.cl COPYONLY)


