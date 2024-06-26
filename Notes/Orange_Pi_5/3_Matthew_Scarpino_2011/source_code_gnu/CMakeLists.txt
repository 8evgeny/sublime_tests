# Build each individual OpenCL program
project(3_Matthew_Scarpino_2011)
include_directories("/usr/local/cuda/include")

EXECUTE_PROCESS( COMMAND uname -m COMMAND tr -d '\n' OUTPUT_VARIABLE ARCHITECTURE )
message( STATUS "Architecture: ${ARCHITECTURE}" )
if( ${ARCHITECTURE} STREQUAL "x86_64" )
    set (OPENCL_LIBRARIES /usr/local/cuda-12.0/targets/x86_64-linux/lib/libOpenCL.so)
else()
    set (OPENCL_LIBRARIES /usr/lib/aarch64-linux-gnu/libOpenCL.so) # Orange Pi5
endif()

add_subdirectory(Ch1/matvec)

add_subdirectory(Ch2/context_count)
add_subdirectory(Ch2/device_ext_test)
add_subdirectory(Ch2/kernel_search)
add_subdirectory(Ch2/platform_ext_test)
add_subdirectory(Ch2/program_build)
add_subdirectory(Ch2/queue_kernel)
