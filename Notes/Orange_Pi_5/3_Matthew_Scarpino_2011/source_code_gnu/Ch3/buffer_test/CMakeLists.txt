add_executable(3_buffer_test buffer_test.c)
target_link_libraries(3_buffer_test ${OpenCL_LIBRARY} )
configure_file(blank.cl ${CMAKE_CURRENT_BINARY_DIR}/blank.cl COPYONLY)

