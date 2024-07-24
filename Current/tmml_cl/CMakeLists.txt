cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 17)
project(tmml_cl)

# Тип корреляции при template matching
# CORR_TYPE = 6 : CCOEFF_NORMED  (Кросскорреляция модифицированная)
# CORR_TYPE = 8 ; COMBINED (объединение прямой и модифицированной кросскорреляции)

set(CORR_TYPE 8)

set(NUM_ITERATIONS 1000)
set(TEMPLATE_WIDTH 48)
set(TEMPLATE_HEIGHT 48)
set(EXT_VAL 5)
set(K_FLOAT_TO_INT 10000)

set(OpenCV_DIR $ENV{HOME}/opencv/install_4_7_0_contrib_cuda)
set(CMAKE_MAKE_PROGRAM "make -j${nproc}")

find_package(OpenCV REQUIRED PATHS ${OpenCV_DIR} NO_DEFAULT_PATH)
include_directories(${OpenCV_DIR})

find_package( OpenCL REQUIRED )
include_directories (${OpenCL_INCLUDE_DIRS} )

if(${NUM_ITERATIONS})
    add_definitions(-DNUM_ITERATIONS=${NUM_ITERATIONS})
endif()
if(${TEMPLATE_WIDTH})
    add_definitions(-DTEMPLATE_WIDTH=${TEMPLATE_WIDTH})
endif()
if(${TEMPLATE_HEIGHT})
    add_definitions(-DTEMPLATE_HEIGHT=${TEMPLATE_HEIGHT})
endif()
if(${EXT_VAL})
    add_definitions(-DEXT_VAL=${EXT_VAL})
endif()
if(${K_FLOAT_TO_INT})
    add_definitions(-DK_FLOAT_TO_INT=${K_FLOAT_TO_INT})
endif()
if(${CORR_TYPE} EQUAL 6)
    add_definitions(-DCCOEFF_NORMED)
    configure_file(6_tmml.cl ${CMAKE_CURRENT_BINARY_DIR}/tmml.cl COPYONLY)
    add_executable(tmml_cl main.cpp tmml_cl.cpp tmml_cl.hpp 6_tmml.cl )
endif()
if(${CORR_TYPE} EQUAL 8)
    add_definitions(-DCOMBINED)
    configure_file(8_tmml.cl ${CMAKE_CURRENT_BINARY_DIR}/tmml.cl COPYONLY)
    add_executable(tmml_cl main.cpp tmml_cl.cpp tmml_cl.hpp 8_tmml.cl )
endif()

target_link_libraries(tmml_cl
    ${OpenCV_LIBS}
    ${OpenCL_LIBRARY}
    )
configure_file(tank_2.png ${CMAKE_CURRENT_BINARY_DIR}/image_source COPYONLY)
