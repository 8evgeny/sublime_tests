add_executable(2_5_SubBufferQuery subbuffer_query.c)
target_link_libraries(2_5_SubBufferQuery ${OPENCL_LIBRARIES} )
configure_file(subbuffer.cl ${CMAKE_CURRENT_BINARY_DIR}/subbuffer.cl COPYONLY)

