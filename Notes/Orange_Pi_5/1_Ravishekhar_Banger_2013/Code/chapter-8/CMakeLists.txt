add_executable( chapter8.MatrixMultiplication MatrixMultiplication.cpp )
target_link_libraries( chapter8.MatrixMultiplication ${OpenCL_LIBRARY} )

add_executable( chapter8.histogram histogram.cpp ${CMAKE_SOURCE_DIR}/common/bmp_image.cpp)
target_link_libraries( chapter8.histogram ${OpenCL_LIBRARY} )
configure_file(${CMAKE_SOURCE_DIR}/input_images/sample_color.bmp ${CMAKE_CURRENT_BINARY_DIR}/sample_color.bmp COPYONLY)

add_executable( chapter8.histogram_cu histogram_cu.cpp ${CMAKE_SOURCE_DIR}/common/bmp_image.cpp)
target_link_libraries( chapter8.histogram_cu ${OpenCL_LIBRARY} )
