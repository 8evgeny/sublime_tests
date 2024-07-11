add_executable(5_shuffle_test shuffle_test.c)
target_link_libraries(5_shuffle_test ${OpenCL_LIBRARY} )
configure_file(shuffle_test.cl ${CMAKE_CURRENT_BINARY_DIR}/shuffle_test.cl COPYONLY)

