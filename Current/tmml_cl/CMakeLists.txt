cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 17)
project(tmml_cl)

# Тип корреляции при template matching
# CORR_TYPE = 2 : SQDIFF_NORMED (Прямая корреляция)
# CORR_TYPE = 8 ; COMBINED (объединение прямой и модифицированной кросскорреляции)
set(CORR_TYPE 8)

set(TEMPLATE_WIDTH 48)
set(EXT_VAL 5)

set(find_diff_result 0)
set(KOEFF2LIB 1) # Коэффициент для получения 8-й либы (при вычитании из 6-й либы 2-й либы).
                 # Если KOEFF2LIB =0, то используется 6-я библиотека (CCOEFF_NORMED  (Кросскорреляция модифицированная)) - CORR_TYPE = 6 - удалена
set(CL_FILE_EXTERN 1) # CL файл во внешнем файле tmml.cl или внутри кода в виде строки
###############################################################

add_definitions(-DKOEFF2LIB=${KOEFF2LIB})

if (${CMAKE_HOST_SYSTEM_PROCESSOR} MATCHES "x86_64")            #Десктоп
    message("SYSTEM_ARCH: ${CMAKE_HOST_SYSTEM_PROCESSOR}")
    set(OpenCV_DIR $ENV{HOME}/opencv/install_4_7_0_contrib_cuda)
    add_definitions(-DARCH_X86_64)
    set(ARCH_ARM 0)
endif()
if (${CMAKE_HOST_SYSTEM_PROCESSOR} MATCHES "aarch64")           #Одноплатники ARM (Khadas, OrangePi5)
    message("SYSTEM_ARCH: ${CMAKE_HOST_SYSTEM_PROCESSOR}")
    set(OpenCV_DIR $ENV{HOME}/opencv/install_4_7_0_contrib)
    add_definitions(-DARCH_ARM)
    set(ARCH_ARM 1)
endif()

set(CMAKE_MAKE_PROGRAM "make -j${nproc}")

if(${CL_FILE_EXTERN} EQUAL 1)
    add_definitions(-DCL_FILE_EXTERN)
endif()

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
add_executable(tmml_cl
    main.cpp
    tmml_cl.cpp
    tmml_cl.hpp
    )

if(${CL_FILE_EXTERN} EQUAL 0)
    target_sources(tmml_cl PRIVATE cl.cpp)
endif()

if(${CL_FILE_EXTERN} EQUAL 1)
    if(${ARCH_ARM} EQUAL 1)
        target_sources(tmml_cl PRIVATE tmml_arm.cl)
        configure_file(tmml_arm.cl ${CMAKE_CURRENT_BINARY_DIR}/tmml_arm.cl COPYONLY)
    endif()
    if(${ARCH_ARM} EQUAL 0)
        target_sources(tmml_cl PRIVATE tmml_x86.cl)
        configure_file(tmml_x86.cl ${CMAKE_CURRENT_BINARY_DIR}/tmml_x86.cl COPYONLY)
    endif()

endif()

target_link_libraries(tmml_cl ${OpenCV_LIBS} ${OpenCL_LIBRARY} )
configure_file(tank_2.png ${CMAKE_CURRENT_BINARY_DIR}/image_source COPYONLY )
