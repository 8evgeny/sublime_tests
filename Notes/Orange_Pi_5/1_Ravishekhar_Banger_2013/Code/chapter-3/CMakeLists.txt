add_executable( chapter3.histogram histogram.cpp ../common/bmp_image.cpp)
target_link_libraries( chapter3.histogram ${OpenCL_LIBRARY} )

add_executable( chapter3.bufferRectangularReads bufferRectangularReads.cpp )
target_link_libraries( chapter3.bufferRectangularReads ${OpenCL_LIBRARY} )

add_executable( chapter3.copyRectangular copyRectangular.cpp )
target_link_libraries( chapter3.copyRectangular ${OpenCL_LIBRARY} )

