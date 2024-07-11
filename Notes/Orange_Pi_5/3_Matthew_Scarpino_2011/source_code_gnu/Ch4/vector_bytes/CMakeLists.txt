add_executable(4_vector_bytes vector_bytes.c)
target_link_libraries(4_vector_bytes ${OpenCL_LIBRARY} )
configure_file(vector_bytes.cl ${CMAKE_CURRENT_BINARY_DIR}/vector_bytes.cl COPYONLY)

