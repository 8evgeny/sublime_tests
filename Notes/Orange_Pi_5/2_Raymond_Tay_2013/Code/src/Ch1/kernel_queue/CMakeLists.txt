add_executable(1_KernelQueue kernel_queue.c)
target_link_libraries(1_KernelQueue ${OPENCL_LIBRARIES} )
configure_file(hello_world.cl ${CMAKE_CURRENT_BINARY_DIR}/hello_world.cl COPYONLY)

