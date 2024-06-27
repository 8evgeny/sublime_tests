    add_executable(2_3_BufferQuery buffer_query.c)
    target_link_libraries(2_3_BufferQuery ${OPENCL_LIBRARIES} )
    configure_file(user_test.cl ${CMAKE_CURRENT_BINARY_DIR}/user_test.cl COPYONLY)


