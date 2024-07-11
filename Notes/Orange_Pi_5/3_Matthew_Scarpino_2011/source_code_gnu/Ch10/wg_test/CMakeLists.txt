add_executable(10_wg_test wg_test.c)
target_link_libraries(10_wg_test ${OpenCL_LIBRARY})
configure_file(blank.cl ${CMAKE_CURRENT_BINARY_DIR}/blank.cl COPYONLY)
