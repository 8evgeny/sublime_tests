cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 17)
project(tmml_2)

# Использование GPU:
set(USE_GPU 1) # (0 - CPU, 1 - CUDA, 2 - OPENCL)

# Тип корреляции при template matching
# CORR_TYPE = 2 : SQDIFF_NORMED (Прямая корреляция)
# CORR_TYPE = 8 ; COMBINED (объединение прямой и модифицированной кросскорреляции)
set(CORR_TYPE 8)

set(TEMPLATE_WIDTH 48)
set(EXT_VAL 5)
set(OpenCV_DIR $ENV{HOME}/opencv/install_4_7_0_contrib_cuda)

set(find_diff_result 0)
set(KOEFF2LIB 1) # Коэффициент для получения 8-й либы (при вычитании из 6-й либы 2-й либы).
                 # Если KOEFF2LIB =0, то используется 6-я библиотека (CCOEFF_NORMED  (Кросскорреляция модифицированная)) - CORR_TYPE = 6 - удалена

###############################################################
add_definitions(-DKOEFF2LIB=${KOEFF2LIB})

set(CMAKE_MAKE_PROGRAM "make -j${nproc}")

find_package(OpenCV REQUIRED PATHS ${OpenCV_DIR} NO_DEFAULT_PATH)
include_directories(${OpenCV_DIR})

if(${find_diff_result} EQUAL 1)
    add_definitions(-Dfind_diff_result)
endif()

if(${USE_GPU} EQUAL 0)
    add_definitions(-DNO_GPU)
    if(${CORR_TYPE} EQUAL 2)
        add_definitions(-DCORR_TYPE=TM_SQDIFF_NORMED)
    endif()
    if(${CORR_TYPE} EQUAL 6)
        add_definitions(-DCORR_TYPE=TM_CCOEFF_NORMED)
    endif()
    if(${CORR_TYPE} EQUAL 8)
        add_definitions(-DCOMBINED)
    endif()
    message(STATUS "--------------------------- NO_GPU")
else()
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
#    set(ccc_major )
#    set(ccc_minor )
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
endif() # END if(${CORR_TYPE} GREATER 0)

#add_definitions(-DGPU_AMPERE)
#message(STATUS "Автоматически не определилось ccc_major - установлено GPU_AMPERE")

if(${TEMPLATE_WIDTH})
    add_definitions(-DTEMPLATE_WIDTH=${TEMPLATE_WIDTH})
endif()
if(${EXT_VAL})
    add_definitions(-DEXT_VAL=${EXT_VAL})
endif()

if(${CORR_TYPE} EQUAL 2)
    add_definitions(-DSQDIFF_NORMED)
endif()
if(${CORR_TYPE} EQUAL 3)
    add_definitions(-DCCORR)
endif()
if(${CORR_TYPE} EQUAL 6)
    add_definitions(-DCCOEFF_NORMED)
endif()
if(${CORR_TYPE} EQUAL 8)
    add_definitions(-DCOMBINED)
endif()

if(${CORR_TYPE} GREATER 0)
    add_executable(${PROJECT_NAME}
        main.cpp
        tmml_2.cpp
        tmml_2.hpp
        tmml_2.cu
        )
    set_target_properties(${PROJECT_NAME} PROPERTIES CUDA_SEPARABLE_COMPILATION ON)
else()
    add_executable(${PROJECT_NAME}
        main.cpp
        tmml_2.cpp
        tmml_2.hpp
        )
endif() # END if(${CORR_TYPE} GREATER 0)
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
set(CMAKE_CUDA_FLAGS "${CMAKE_CUDA_FLAGS} \
    -Xptxas -O1 \
    --dopt=on \
    -use_fast_math \
    -v \
    --extra-device-vectorization \
    ")

