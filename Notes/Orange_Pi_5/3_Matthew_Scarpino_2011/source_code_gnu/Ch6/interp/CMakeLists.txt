add_executable(6_interp interp.c)
target_link_libraries(6_interp
    ${OpenCL_LIBRARY}
    png
    )
configure_file(interp.cl ${CMAKE_CURRENT_BINARY_DIR}/interp.cl COPYONLY)
configure_file(input.png ${CMAKE_CURRENT_BINARY_DIR}/input.png COPYONLY)
