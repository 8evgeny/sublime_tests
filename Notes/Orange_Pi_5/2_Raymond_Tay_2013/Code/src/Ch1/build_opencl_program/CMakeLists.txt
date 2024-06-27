add_executable(1_BuildOpenCLProgram build_opencl_program.c)
target_link_libraries(1_BuildOpenCLProgram ${OPENCL_LIBRARIES} )
configure_file(simple.cl ${CMAKE_CURRENT_BINARY_DIR}/simple.cl COPYONLY)
configure_file(simple_2.cl ${CMAKE_CURRENT_BINARY_DIR}/simple_2.cl COPYONLY)


