cmake_minimum_required(VERSION 2.8)

set (DEBUG ON)

find_package(OpenCL REQUIRED)

if(CMAKE_COMPILER_IS_GNUCC)
    if (CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64")
        set (COMPILE_ARCH -m64)
    endif()
    if (CMAKE_SYSTEM_PROCESSOR STREQUAL "x86")
        set (COMPILE_ARCH -m32)
    endif()

    if (DEBUG EQUAL ON)
        set (CMAKE_C_FLAGS "-std=c99 -Wall -DUNIX -g -DDEBUG ${COMPILE_ARCH}")
    else()
        set (CMAKE_C_FLAGS "-std=c99 -Wall -DUNIX ${COMPILE_ARCH}")
    endif()

    add_executable(2_7_CopyBuffer copy_buffer.c)
    target_link_libraries(2_7_CopyBuffer ${OPENCL_LIBRARIES} )
    configure_file(copy_buffer.cl ${CMAKE_CURRENT_BINARY_DIR}/copy_buffer.cl COPYONLY)

endif(CMAKE_COMPILER_IS_GNUCC)

