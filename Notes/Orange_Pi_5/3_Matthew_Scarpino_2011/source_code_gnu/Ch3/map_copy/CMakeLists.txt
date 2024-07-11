add_executable(3_map_copy map_copy.c)
target_link_libraries(3_map_copy ${OpenCL_LIBRARY} )
configure_file(blank.cl ${CMAKE_CURRENT_BINARY_DIR}/blank.cl COPYONLY)

