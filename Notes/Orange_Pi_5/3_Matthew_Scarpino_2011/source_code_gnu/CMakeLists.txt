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
