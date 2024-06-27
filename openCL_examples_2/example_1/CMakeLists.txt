add_executable(example_1 host.c)
target_link_libraries(example_1 ${OpenCL_LIBRARY} )
configure_file(kernel.cl ${CMAKE_CURRENT_BINARY_DIR}/kernel.cl COPYONLY)



