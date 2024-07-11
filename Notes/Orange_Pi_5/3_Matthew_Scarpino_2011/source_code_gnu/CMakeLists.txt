cmake_minimum_required(VERSION 3.22)
project(3_Matthew_Scarpino_2011)

find_package( OpenCL REQUIRED )
include_directories (${OpenCL_INCLUDE_DIRS})
set (CMAKE_C_FLAGS "-std=c99 -Wall -DUNIX ${COMPILE_ARCH}")

add_subdirectory(Ch1/matvec)

add_subdirectory(Ch2/context_count)
add_subdirectory(Ch2/device_ext_test)
add_subdirectory(Ch2/kernel_search)
add_subdirectory(Ch2/platform_ext_test)
add_subdirectory(Ch2/program_build)
add_subdirectory(Ch2/queue_kernel)

add_subdirectory(Ch3/buffer_check)
add_subdirectory(Ch3/buffer_test)
add_subdirectory(Ch3/map_copy)

add_subdirectory(Ch4/double_test)
add_subdirectory(Ch4/float_config)
add_subdirectory(Ch4/hello_kernel)
add_subdirectory(Ch4/vector_bytes)
add_subdirectory(Ch4/vector_widths)

add_subdirectory(Ch5/id_check)
add_subdirectory(Ch5/mad_test)
add_subdirectory(Ch5/mod_round)
add_subdirectory(Ch5/op_test)
add_subdirectory(Ch5/polar_rect)
add_subdirectory(Ch5/select_test)
add_subdirectory(Ch5/shuffle_test)

add_subdirectory(Ch6/interp)
add_subdirectory(Ch6/simple_image)




add_subdirectory(Ch10/reduction)
add_subdirectory(Ch10/reduction_complete)
add_subdirectory(Ch10/wg_test)
