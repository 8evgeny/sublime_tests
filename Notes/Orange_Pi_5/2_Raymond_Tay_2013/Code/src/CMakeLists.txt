project(2_Raymond_Tay_2013)

#include_directories("/usr/local/cuda/include")
#EXECUTE_PROCESS( COMMAND uname -m COMMAND tr -d '\n' OUTPUT_VARIABLE ARCHITECTURE )
#message( STATUS "Architecture: ${ARCHITECTURE}" )
#if( ${ARCHITECTURE} STREQUAL "x86_64" )
#    set (OPENCL_LIBRARIES /usr/local/cuda-12.0/targets/x86_64-linux/lib/libOpenCL.so)
#else()
#    set (OPENCL_LIBRARIES /usr/lib/aarch64-linux-gnu/libOpenCL.so) # Orange Pi5
#endif()

SET (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/modules")
INCLUDE(FindSSE)
FindSSE ()
IF(SSE3_FOUND)
    IF(SSSE3_FOUND)
            SET(CXX_DFLAGS -msse3 -mssse3)
    ENDIF(SSSE3_FOUND)
ENDIF(SSE3_FOUND)

IF(SSE4_2_FOUND)
        SET(CXX_DFLAGS -msse4.2 -mpopcnt)
ENDIF(SSE4_2_FOUND)
ADD_DEFINITIONS(${CXX_DFLAGS})

find_package( OpenCL REQUIRED )
set (OPENCL_LIBRARIES ${OpenCL_LIBRARY})
message("OPENCL_LIBRARIES: " ${OPENCL_LIBRARIES})
include_directories (${OpenCL_INCLUDE_DIRS})

set (CMAKE_C_FLAGS "-std=c99 -Wall -DUNIX ${COMPILE_ARCH}")

add_subdirectory(Ch1/build_opencl_program)
add_subdirectory(Ch1/context_query)
add_subdirectory(Ch1/device_details)
add_subdirectory(Ch1/device_extensions)
add_subdirectory(Ch1/kernel_query)
add_subdirectory(Ch1/kernel_queue)
add_subdirectory(Ch1/platform_details)

add_subdirectory(Ch2/user_buffer)
add_subdirectory(Ch2/user_buffer_alignment)
add_subdirectory(Ch2/buffer_query)
add_subdirectory(Ch2/sub_buffers)
add_subdirectory(Ch2/sub_buffer_query)
add_subdirectory(Ch2/events)
add_subdirectory(Ch2/copy_buffer)
add_subdirectory(Ch2/work_partitioning)
add_subdirectory(Ch2/simple_2D_readwrite)



add_subdirectory(Ch3/byte_ordering)
add_subdirectory(Ch3/vectorization) # Не работает только на Orange Pi 5
add_subdirectory(Ch3/double_support)

add_subdirectory(Ch4/simple_vector_load)
add_subdirectory(Ch4/simple_vector_store)
add_subdirectory(Ch4/simple_dot_product)
add_subdirectory(Ch4/par_min)
add_subdirectory(Ch4/simple_fma_vs_mad)
add_subdirectory(Ch4/simple_rounding)
add_subdirectory(Ch4/simple_select_filter)
add_subdirectory(Ch4/simple_shuffle)
add_subdirectory(Ch4/simple_trigonometry)

add_subdirectory(Ch5/histogram)
add_subdirectory(Ch5/histogram_c)
#add_subdirectory(Ch5/histogram_boost)

add_subdirectory(Ch6/sobelfilter)

add_subdirectory(Ch7/matrix_multiplication_01)
add_subdirectory(Ch7/matrix_multiplication_02)
add_subdirectory(Ch7/matrix_multiplication_03)
add_subdirectory(Ch7/matrix_multiplication_04)

#add_subdirectory(Ch8/SpMV_VexCL)   # BOOST
#add_subdirectory(Ch8/SpMV) #include "Spmv.h"

#add_subdirectory(Ch9/BitonicSort_CPU_01)
#add_subdirectory(Ch9/BitonicSort_CPU_02)
#add_subdirectory(Ch9/BitonicSort_GPU_01)
#add_subdirectory(Ch9/BitonicSort_GPU_02)

#add_subdirectory(Ch10/QuickSort_Binary)
#add_subdirectory(Ch10/MSDRadixSort_CPU)
#add_subdirectory(Ch10/RadixSort_CPU)
#add_subdirectory(Ch10/RadixSort_GPU)
#add_subdirectory(Ch10/Reduction)

