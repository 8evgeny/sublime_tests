add_executable(example_1 host.cpp)
target_link_libraries(example_1 ${OpenCL_LIBRARY} )
configure_file(mandelbrot.cl ${CMAKE_CURRENT_BINARY_DIR}/mandelbrot.cl COPYONLY)



