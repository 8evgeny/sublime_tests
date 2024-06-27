add_executable(2_program_build program_build.c)
target_link_libraries(2_program_build ${OpenCL_LIBRARY} )
configure_file(bad.cl ${CMAKE_CURRENT_BINARY_DIR}/bad.cl COPYONLY)
configure_file(good.cl ${CMAKE_CURRENT_BINARY_DIR}/good.cl COPYONLY)



