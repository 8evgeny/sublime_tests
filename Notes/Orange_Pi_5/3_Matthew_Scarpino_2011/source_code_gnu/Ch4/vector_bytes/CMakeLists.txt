add_executable(4_double_test double_test.c)
target_link_libraries(4_double_test ${OpenCL_LIBRARY} )
configure_file(double_test.cl ${CMAKE_CURRENT_BINARY_DIR}/double_testcl COPYONLY)

