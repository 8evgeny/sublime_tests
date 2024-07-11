add_executable(5_polar_rect polar_rect.c)
target_link_libraries(5_polar_rect ${OpenCL_LIBRARY} )
configure_file(polar_rect.cl ${CMAKE_CURRENT_BINARY_DIR}/polar_rect.cl COPYONLY)

