cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 17)
project(tmml_cl)

# Тип корреляции при template matching
# CORR_TYPE = 2 : SQDIFF_NORMED (Прямая корреляция)
# CORR_TYPE = 6 : CCOEFF_NORMED  (Кросскорреляция модифицированная)
# CORR_TYPE = 8 ; COMBINED (объединение прямой и модифицированной кросскорреляции)
set(CORR_TYPE 8)

set(TEMPLATE_WIDTH 48)
set(EXT_VAL 5)
set(OpenCV_DIR $ENV{HOME}/opencv/install_4_7_0_contrib)
set(find_diff_result 1)

###############################################################

set(CMAKE_MAKE_PROGRAM "make -j${nproc}")

find_package(OpenCV REQUIRED PATHS ${OpenCV_DIR} NO_DEFAULT_PATH)
include_directories(${OpenCV_DIR})
include_directories($CMAKE_SOURCE_DIR})
find_package(OpenCL REQUIRED)
include_directories (${OpenCL_INCLUDE_DIRS})

if(${TEMPLATE_WIDTH})
    add_definitions(-DTEMPLATE_WIDTH=${TEMPLATE_WIDTH})
endif()
if(${EXT_VAL})
    add_definitions(-DEXT_VAL=${EXT_VAL})
endif()
if(${CORR_TYPE} EQUAL 6)
    add_definitions(-DCCOEFF_NORMED)
endif()
if(${CORR_TYPE} EQUAL 8)
    add_definitions(-DCOMBINED)
endif()
if(${find_diff_result} EQUAL 1)
    add_definitions(-Dfind_diff_result)
endif()
add_executable(tmml_cl main.cpp tmml_cl.cpp tmml_cl.hpp tmml.cl )
configure_file(tmml.cl ${CMAKE_CURRENT_BINARY_DIR}/tmml.cl COPYONLY)

target_link_libraries(tmml_cl ${OpenCV_LIBS} ${OpenCL_LIBRARY} )
configure_file(tank_2.png ${CMAKE_CURRENT_BINARY_DIR}/image_source COPYONLY )
