cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 17)
project(tmml_OpenCL)

# Тип корреляции при template matching
# CORR_TYPE = 2 : SQDIFF_NORMED (Прямая корреляция)
# CORR_TYPE = 6 : CCOEFF_NORMED  (Кросскорреляция модифицированная)
# CORR_TYPE = 8 ; COMBINED (объединение прямой и модифицированной кросскорреляции)
set(CORR_TYPE 2)

set(TEMPLATE_WIDTH 48)
set(TEMPLATE_HEIGHT 48)
set(EXT_VAL 5)
set(OpenCV_DIR $ENV{HOME}/opencv/install_4_7_0_contrib_cuda)

set(CMAKE_MAKE_PROGRAM "make -j${nproc}")

find_package(OpenCV REQUIRED PATHS ${OpenCV_DIR} NO_DEFAULT_PATH)
include_directories(${OpenCV_DIR})

find_package( OpenCL REQUIRED )
find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Gui Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Gui Widgets REQUIRED)
include_directories (${OpenCL_INCLUDE_DIRS} )

set(CMAKE_CUDA_COMPILER /usr/local/cuda/bin/nvcc)
option(USE_CUDA "Use CUDA" ON)
enable_language("CUDA")
find_package(CUDA REQUIRED)
include_directories(${CUDA_INCLUDE_DIRS})

#Get CUDA compute capability
include(FindCUDA/select_compute_arch)
CUDA_DETECT_INSTALLED_GPUS(INSTALLED_GPU_CCS_1)
string(STRIP "${INSTALLED_GPU_CCS_1}" INSTALLED_GPU_CCS_2)
string(REPLACE " " ";" INSTALLED_GPU_CCS_3 "${INSTALLED_GPU_CCS_2}")
string(REPLACE "." "" CUDA_ARCH_LIST "${INSTALLED_GPU_CCS_3}")
SET(CMAKE_CUDA_ARCHITECTURES ${CUDA_ARCH_LIST})
message(STATUS "=================CUDA_ARCH_LIST:${CUDA_ARCH_LIST}")
string(SUBSTRING "${CUDA_ARCH_LIST}" 0 1 ccc_major)
string(SUBSTRING "${CUDA_ARCH_LIST}" 1 1 ccc_minor)
message(STATUS "=================ccc_major:${ccc_major}")
message(STATUS "=================ccc_minor:${ccc_minor}")

if(${ccc_major} STREQUAL "8")
    add_definitions(-DGPU_AMPERE)
    message(STATUS "GPU_AMPERE (видеокарты серии 30ХХ)")
elseif(${ccc_major} STREQUAL "7")
    add_definitions(-DGPU_VOLTA)
    message(STATUS "GPU_VOLTA (XAVIER NX)")
else()
    add_definitions(-DGPU_AMPERE)
    message(STATUS "Автоматически не определилось ccc_major - установлено GPU_AMPERE")
endif()

#add_definitions(-DGPU_AMPERE)
#message(STATUS "Автоматически не определилось ccc_major - установлено GPU_AMPERE")

if(${TEMPLATE_WIDTH})
    add_definitions(-DTEMPLATE_WIDTH=${TEMPLATE_WIDTH})
endif()
if(${TEMPLATE_HEIGHT})
    add_definitions(-DTEMPLATE_HEIGHT=${TEMPLATE_HEIGHT})
endif()
if(${EXT_VAL})
    add_definitions(-DEXT_VAL=${EXT_VAL})
endif()

if(${CORR_TYPE} EQUAL 2)
    add_definitions(-DSQDIFF_NORMED)
endif()
if(${CORR_TYPE} EQUAL 6)
    add_definitions(-DCCOEFF_NORMED)
endif()
if(${CORR_TYPE} EQUAL 8)
    add_definitions(-DCOMBINED)
endif()

add_executable(tmml_openCL
    main.cpp
    tmml.cpp
    tmml.hpp
    tmml.cu
    openCL.cpp
    openCL.hpp
    )
set_target_properties(tmml_openCL PROPERTIES CUDA_SEPARABLE_COMPILATION ON)
target_link_libraries(tmml_openCL
    ${OpenCV_LIBS}
    ${OpenCL_LIBRARY}
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    )
configure_file(matching.cl ${CMAKE_CURRENT_BINARY_DIR}/matching.cl COPYONLY)
configure_file(tank_2.png ${CMAKE_CURRENT_BINARY_DIR}/image_source COPYONLY)
