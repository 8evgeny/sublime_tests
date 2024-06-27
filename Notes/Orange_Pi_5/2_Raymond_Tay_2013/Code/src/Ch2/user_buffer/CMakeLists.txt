add_executable(2_1_UserBuffer user_buffer.c)
target_link_libraries(2_1_UserBuffer ${OPENCL_LIBRARIES} )
configure_file(user_test.cl ${CMAKE_CURRENT_BINARY_DIR}/user_test.cl COPYONLY)


