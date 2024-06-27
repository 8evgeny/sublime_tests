add_executable(1_matvec matvec.c)
target_link_libraries(1_matvec ${OpenCL_LIBRARY} )
configure_file(matvec.cl ${CMAKE_CURRENT_BINARY_DIR}/matvec.cl COPYONLY)


