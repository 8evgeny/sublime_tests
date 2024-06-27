project(OpenCL_examples)

find_package( OpenCL REQUIRED )
include_directories (${OpenCL_INCLUDE_DIRS} )
set (CMAKE_C_FLAGS "-std=c99 -Wall -DUNIX ${COMPILE_ARCH}")

add_subdirectory(example_1)


