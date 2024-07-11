add_executable(5_mod_round mod_round.c)
target_link_libraries(5_mod_round ${OpenCL_LIBRARY} )
configure_file(mod_round.cl ${CMAKE_CURRENT_BINARY_DIR}/mod_round.cl COPYONLY)

