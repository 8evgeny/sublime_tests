add_executable(2_4_SubBuffer sub_buffer.c)
target_link_libraries(2_4_SubBuffer ${OPENCL_LIBRARIES} )
configure_file(sub_buffer.cl ${CMAKE_CURRENT_BINARY_DIR}/sub_buffer.cl COPYONLY)


