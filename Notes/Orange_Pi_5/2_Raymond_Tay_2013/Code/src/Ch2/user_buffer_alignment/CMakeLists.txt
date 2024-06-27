add_executable(2_2_UserBufferAlign user_buffer_align.c)
target_link_libraries(2_2_UserBufferAlign ${OPENCL_LIBRARIES} )
configure_file(user_test.cl ${CMAKE_CURRENT_BINARY_DIR}/user_test.cl COPYONLY)


