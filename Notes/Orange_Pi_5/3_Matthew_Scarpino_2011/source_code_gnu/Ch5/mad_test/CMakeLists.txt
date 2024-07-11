add_executable(5_mad_test mad_test.c)
target_link_libraries(5_mad_test ${OpenCL_LIBRARY} )
configure_file(mad_test.cl ${CMAKE_CURRENT_BINARY_DIR}/mad_test.cl COPYONLY)

