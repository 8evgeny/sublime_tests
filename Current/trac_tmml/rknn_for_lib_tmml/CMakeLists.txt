cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 14)

message(STATUS "")
message(STATUS " Алгоритм генерации библиотеки для Rockchip Orange Pi 5")
project(rknn_for_lib_tmml)

set(NNET_LIB _trac_tmml_RKNN)

# Тип экстраполяции трака (0) - по крайним точкам, (1) - МНК, (2) - Калман:
set(USE_polinom 0)

set(work_in round) # Работа в круге, вписанном в центр фрейма (round), либо во всём фрейме (rect).
# set(work_in rect) # Работа в круге, вписанном в центр фрейма (round), либо во всём фрейме (rect).

set(OpenCV_DIR $ENV{HOME}/opencv/install_4_7_0_contrib_static)

set(FROM_LIB ${CMAKE_CURRENT_LIST_DIR}/../trac_from_lib_tmml/)

set(rknn_enable 1) # RKNN API
set (RKNN_API_DIRECTORY ${CMAKE_SOURCE_DIR}/RKNN_API)
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


############################## IF RKNN_ENABLE:
if(${rknn_enable} EQUAL 1)

   add_definitions(-DRKNN_ENABLE)
   message("----- RKNN enable")
   add_definitions(-DRKNN_API="${RKNN_API_DIRECTORY}/yolov8.h")

   set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
   message("CMAKE_MODULE_PATH = " ${CMAKE_MODULE_PATH} )

   include_directories(
       ${OPENCV_INCLUDE_DIRS}
       ${RKNN_API_DIRECTORY}/3rdparty/rknpu2/include
       ${RKNN_API_DIRECTORY}/utils
       ${RKNN_API_DIRECTORY}
   )
   add_library(${NNET_LIB} SHARED
       nnet_scan.hpp
       nnet_scan.cpp
       nnet_rknn.cpp
       ${RKNN_API_DIRECTORY}/postprocess.cc
       ${RKNN_API_DIRECTORY}/yolov8.cc
       ${FROM_LIB}tracshats/trac_api.hpp
       ${FROM_LIB}tracshats/trac_struct.hpp
       )

   add_subdirectory(${RKNN_API_DIRECTORY}/3rdparty/ 3rdparty.out)
   add_subdirectory(${RKNN_API_DIRECTORY}/utils/ utils.out)

   set(THREADS_PREFER_PTHREAD_FLAG ON)
   find_package(Threads REQUIRED)
   target_link_libraries(${NNET_LIB}
       Threads::Threads
       imageutils
       fileutils
       imagedrawing
       ${RKNN_API_DIRECTORY}/lib/librknnrt.so
       ${RKNN_API_DIRECTORY}/lib/librga.so
       dl
       )

   target_link_libraries(${NNET_LIB} PRIVATE )
   target_link_libraries(${NNET_LIB} PRIVATE )
endif() # if(${rknn_enable} EQUAL 1)
