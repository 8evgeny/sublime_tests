add_executable(10_reduction reduction.c)
target_link_libraries(10_reduction ${OpenCL_LIBRARY})
configure_file(reduction.cl ${CMAKE_CURRENT_BINARY_DIR}/reduction.cl COPYONLY)
