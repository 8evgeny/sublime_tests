add_executable(5_id_check id_check.c)
target_link_libraries(5_id_check ${OpenCL_LIBRARY} )
configure_file(id_check.cl ${CMAKE_CURRENT_BINARY_DIR}/id_check.cl COPYONLY)

