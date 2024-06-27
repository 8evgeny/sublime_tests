add_executable( chapter4.getSupportedImageFormats getSupportedImageFormats.cpp )
target_link_libraries( chapter4.getSupportedImageFormats ${OpenCL_LIBRARY} )

add_executable( chapter4.histogram_image histogram_image.cpp ../common/bmp_image.cpp )
target_link_libraries( chapter4.histogram_image ${OpenCL_LIBRARY} )

add_executable( chapter4.image_sampler image_sampler.cpp )
target_link_libraries( chapter4.image_sampler ${OpenCL_LIBRARY} )
