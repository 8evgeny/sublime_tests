cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 14)

message(STATUS "")
message(STATUS " Алгоритм генерации библиотеки for neural network")
project(nnet_for_lib_tmml)

# Тип экстраполяции трака (0) - по крайним точкам, (1) - МНК, (2) - Калман:
set(USE_polinom 0)

set(work_in round) # Работа в круге, вписанном в центр фрейма (round), либо во всём фрейме (rect).
# set(work_in rect) # Работа в круге, вписанном в центр фрейма (round), либо во всём фрейме (rect).

set(FROM_LIB ${CMAKE_CURRENT_LIST_DIR}/../trac_from_lib_tmml/)

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

if(${FIND_DISC_ID} EQUAL 1)
  add_definitions(-DFIND_DISC_ID)
  message("----- FIND_DISC_ID enable")
endif() # END if(${FIND_DISC_ID} EQUAL 1)

if(${CMAKE_HOST_SYSTEM_VERSION} MATCHES "rockchip$") #OrangePi
    message("set rknn_enable")
    set(NNET_LIB _trac_tmml_RKNN)
    set(RKNN_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/RKNN_API)
    add_definitions(-DRKNN_ENABLE)
    message("----- RKNN enable")
    add_definitions(-DRKNN_API="${RKNN_DIRECTORY}/yolov8.h")
    link_directories(${RKNN_DIRECTORY})

    file(COPY ${RKNN_DIRECTORY}/model DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
    add_subdirectory(${RKNN_DIRECTORY}/3rdparty/ 3rdparty.out)
    add_subdirectory(${RKNN_DIRECTORY}/utils/ utils.out)
    file(GLOB RKNN_SRC ${RKNN_DIRECTORY}/*.cc)

    add_library(${NNET_LIB} SHARED
        ${RKNN_SRC}
        nnet_scan.hpp
        nnet_scan.cpp
        nnet_rknn.cpp
        ${FROM_LIB}tracshats/trac_api.hpp
        ${FROM_LIB}tracshats/trac_struct.hpp
        )

   target_include_directories(${NNET_LIB} PRIVATE
       ${FROM_LIB}tracshats
       ${RKNN_DIRECTORY}
       ${CMAKE_CURRENT_SOURCE_DIR}
       ${RKNN_DIRECTORY}/3rdparty/rknpu2/include
       ${RKNN_DIRECTORY}/3rdparty/opencv/opencv-linux-aarch64/include/opencv2
   )

    set(THREADS_PREFER_PTHREAD_FLAG ON)
    find_package(Threads REQUIRED)
    target_link_libraries(${NNET_LIB}
        Threads::Threads
        imageutils
        fileutils
        imagedrawing
        ${RKNN_DIRECTORY}/lib/librknnrt.so
        ${RKNN_DIRECTORY}/lib/librga.so
        dl
        )
else() #CUDA
    message("set trt_enable")
    set(NNET_LIB _trac_tmml_TKDNN)
    set(TKDNN_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/../../tkDNN)
    add_definitions(-DTRT_ENABLE)
    message("----- TensorRT enable")
    add_definitions(-DTRT_API="${TKDNN_DIRECTORY}/yolo_trt_api.hpp")
    link_directories(${TKDNN_DIRECTORY})
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
    message("CMAKE_MODULE_PATH = " ${CMAKE_MODULE_PATH} )
    ###### CUDA ######
    find_package(CUDA REQUIRED)
    find_package(CUDNN REQUIRED)
    set(OpenCV_DIR $ENV{HOME}/opencv/install_4_7_0_contrib_cuda_static)
    find_package(OpenCV REQUIRED PATHS ${OpenCV_DIR} NO_DEFAULT_PATH)
    include_directories(
        ${TKDNN_DIRECTORY}
        ${OPENCV_INCLUDE_DIRS}
        ${NVINFER_INCLUDES}
        ${CUDA_INCLUDE_DIRS}
        ${CUDNN_INCLUDE_DIR}
        ${OpenCV_DIR}
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

endif() # if(${CMAKE_HOST_SYSTEM_VERSION}



