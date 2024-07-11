add_executable(6_simple_image simple_image.c)
target_link_libraries(6_simple_image
    ${OpenCL_LIBRARY}
    png
    )
configure_file(simple_image.cl ${CMAKE_CURRENT_BINARY_DIR}/simple_image.cl COPYONLY)
configure_file(blank.png ${CMAKE_CURRENT_BINARY_DIR}/blank.png COPYONLY)
