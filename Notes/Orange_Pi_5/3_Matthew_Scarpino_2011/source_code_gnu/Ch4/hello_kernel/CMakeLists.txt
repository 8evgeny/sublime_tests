add_executable(4_hello_kernel hello_kernel.c)
target_link_libraries(4_hello_kernel ${OpenCL_LIBRARY} )
configure_file(hello_kernel.cl ${CMAKE_CURRENT_BINARY_DIR}/hello_kernel.cl COPYONLY)

