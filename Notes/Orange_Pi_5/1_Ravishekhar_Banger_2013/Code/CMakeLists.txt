# This is the root cmake file. This one shall be used to create the
# different project build related files

cmake_minimum_required( VERSION 2.8 )
project( 1_Ravishekhar_Banger_2013 )

EXECUTE_PROCESS( COMMAND uname -m COMMAND tr -d '\n' OUTPUT_VARIABLE ARCHITECTURE )
message( STATUS "Architecture: ${ARCHITECTURE}" )

set( CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR} )
find_package( OpenCL REQUIRED )
if( ${ARCHITECTURE} STREQUAL "x86_64" )
    set (OPENCL_LIBRARIES /usr/local/cuda-12.0/targets/x86_64-linux/lib/libOpenCL.so)
else()
    set (OPENCL_LIBRARIES /usr/lib/aarch64-linux-gnu/libOpenCL.so) # Orange Pi5
endif()

#message($"{OPENCL_LIBRARIES}" ${OPENCL_LIBRARIES})
include_directories ("${PROJECT_SOURCE_DIR}/include" ${OpenCL_INCLUDE_DIRS})
SUBDIRS( chapter-1/
         chapter-2/
         chapter-3/
         chapter-4/
         chapter-5/
         chapter-6/
         chapter-7/
         chapter-8/
         chapter-9/
         chapter-11/
         )
