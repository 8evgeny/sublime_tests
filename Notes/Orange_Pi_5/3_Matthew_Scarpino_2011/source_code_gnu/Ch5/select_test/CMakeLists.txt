add_executable(5_select_test select_test.c)
target_link_libraries(5_select_test ${OpenCL_LIBRARY} )
configure_file(select_test.cl ${CMAKE_CURRENT_BINARY_DIR}/select_test.cl COPYONLY)

