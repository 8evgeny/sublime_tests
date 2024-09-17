cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 14)

message(STATUS "")
message(STATUS " Алгоритм генерации библиотеки для сканирующего коптера")
project(nnet_for_lib_tmml)

set(NNET_LIB _trac_tmml_TKDNN)

# Тип экстраполяции трака (0) - по крайним точкам, (1) - МНК, (2) - Калман:
set(USE_polinom 0)

set(work_in round) # Работа в круге, вписанном в центр фрейма (round), либо во всём фрейме (rect).
# set(work_in rect) # Работа в круге, вписанном в центр фрейма (round), либо во всём фрейме (rect).

set(OpenCV_DIR $ENV{HOME}/opencv/install_4_7_0_contrib_cuda_static)

set(FROM_LIB ${CMAKE_CURRENT_LIST_DIR}/../trac_from_lib_tmml/)

set(trt_enable 1) # TensorRT
set(yolo_enable 0) # Yolo
set(USE_YOLO_VERSION v4) # Использование версии Yolo (v3 или v4):
set(FIND_DISC_ID 0) # Привязка к железу вычислителя.
##################################################################################################
set(threads_num ${nproc}) # Число потоков компиляции:
set(CMAKE_MAKE_PROGRAM "${CMAKE_MAKE_PROGRAM} -j${threads_num}")

if(${USE_polinom} EQUAL 0)
    add_definitions(-DPolinom0)
elseif(${USE_polinom} EQUAL 1)
    add_definitions(-DPolinom1)
elseif(${USE_polinom} EQUAL 2)
    add_definitions(-DPolinom2)
endif() # if(${USE_polinom} EQUAL 2)

add_definitions(-DTRAC_API="${FROM_LIB}tracshats/trac_api.hpp")
add_definitions(-DOPENCV)

if(${work_in} STREQUAL round)
  add_definitions(-DWORK_IN_ROUND)
  message(STATUS "========================== work_in round")
endif() # if(${work_in} STREQUAL round)

if(${work_in} STREQUAL rect)
  add_definitions(-DWORK_IN_RECT)
  message(STATUS "========================== work_in rect")
endif() # if(${work_in} STREQUAL rect)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${FROM_LIB}lib)

include(${CMAKE_CURRENT_LIST_DIR}/opencv_static.cmake)

find_package(OpenCV REQUIRED PATHS ${OpenCV_DIR} NO_DEFAULT_PATH)
include_directories(${OpenCV_DIR})

if(${FIND_DISC_ID} EQUAL 1)
  add_definitions(-DFIND_DISC_ID)
  message("----- FIND_DISC_ID enable")
endif() # END if(${FIND_DISC_ID} EQUAL 1)

############################## IF YOLO_ENABLE:
if(${yolo_enable} EQUAL 1)
    set(YOLO_LIB_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/../../darknet4)
    link_directories(${YOLO_LIB_DIRECTORY})
    add_definitions(-DYOLO_ENABLE)
    add_definitions(-DYOLO_${USE_YOLO_VERSION})
    message("Use yolo version = " YOLO_${USE_YOLO_VERSION})
    add_definitions(-DYOLO_API="$ENV{HOME}/QtProg/darknet4/include/yolo_v2_class_${USE_YOLO_VERSION}.hpp")

    message(STATUS "--------------------------- LIB ${NNET_LIB}")
    add_library(${NNET_LIB} SHARED
        nnet_scan.hpp
        nnet_scan.cpp
        nnet_yolo.cpp
        ${FROM_LIB}tracshats/trac_api.hpp
        ${FROM_LIB}tracshats/trac_struct.hpp
        )
    target_link_libraries(${NNET_LIB} ${CUDA_LIBRARIES})
    target_link_libraries(${NNET_LIB} ${CUDA_LIBRARIES})
endif() # if(${yolo_enable} EQUAL 1)

############################## IF TRT_ENABLE:
if(${trt_enable} EQUAL 1)
   set(TKDNN_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/../../tkDNN)
   add_definitions(-DTRT_ENABLE)
   message("----- TensorRT enable")
   add_definitions(-DTRT_API="${TKDNN_DIRECTORY}/yolo_trt_api.hpp")
   link_directories(${TKDNN_DIRECTORY})
   set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
   message("CMAKE_MODULE_PATH = " ${CMAKE_MODULE_PATH} )
   ###### CUDA ######
#   find_package(CUDA REQUIRED)
#   find_package(CUDNN REQUIRED)
   include_directories(
       ${TKDNN_DIRECTORY}
       ${OPENCV_INCLUDE_DIRS}
       ${NVINFER_INCLUDES}
       ${CUDA_INCLUDE_DIRS}
       ${CUDNN_INCLUDE_DIR}
   )
   add_library(${NNET_LIB} SHARED
       nnet_scan.hpp
       nnet_scan.cpp
       nnet_trt.cpp
       ${FROM_LIB}tracshats/trac_api.hpp
       ${FROM_LIB}tracshats/trac_struct.hpp
       )
   target_link_libraries(${NNET_LIB} PRIVATE ${CUDA_LIBRARIES} ${CUDA_CUBLAS_LIBRARIES} ${CUDNN_LIBRARIES} -ltkDNN -lkernels -ltkdnn_yolo)
   target_link_libraries(${NNET_LIB} PRIVATE ${CUDA_LIBRARIES} ${CUDA_CUBLAS_LIBRARIES} ${CUDNN_LIBRARIES} -ltkDNN -lkernels -ltkdnn_yolo)
   target_link_libraries(${NNET_LIB} PRIVATE ${CUDA_LIBRARIES} ${CUDA_CUBLAS_LIBRARIES} ${CUDNN_LIBRARIES} -ltkDNN -lkernels -ltkdnn_yolo)
endif() # if(${trt_enable} EQUAL 1)
