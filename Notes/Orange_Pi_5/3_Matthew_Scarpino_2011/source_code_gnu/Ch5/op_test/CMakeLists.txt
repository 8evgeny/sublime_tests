add_executable(5_op_test op_test.c)
target_link_libraries(5_op_test ${OpenCL_LIBRARY} )
configure_file(op_test.cl ${CMAKE_CURRENT_BINARY_DIR}/op_test.cl COPYONLY)

