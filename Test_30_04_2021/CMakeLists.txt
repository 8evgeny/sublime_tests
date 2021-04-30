cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 14)
project(test_radar)
file(GLOB sources src/*)
add_executable(${PROJECT_NAME} ${sources})

set (Boost_USE_MULTITHREADED ON)
find_package (Boost REQUIRED COMPONENTS system filesystem )
if (Boost_FOUND)
    message("cmake message-" ${PROJECT_NAME} " boost include DIR: " ${Boost_INCLUDE_DIR})
    include_directories (SYSTEM ${Boost_INCLUDE_DIR})
endif ()


#set(OpenCV_DIR ${THIRD_PARTY_INSTALL_DIR}/lib/cmake/opencv4 CACHE PATH "")
#set(OpenCV_DIR /home/jhon/sadko/third-party/build/install/x86_64/lib/cmake/opencv4 CACHE PATH "")
#message(STATUS "    OpenCV_DIR: ${OpenCV_DIR}")


#SET(OpenCV_INSTALL_PATH /usr)
#SET(OpenCV_INCLUDE_DIRS "${OpenCV_INSTALL_PATH}/include/opencv4;${OpenCV_INSTALL_PATH}/include")
#SET(OpenCV_LIB_DIR "${OpenCV_INSTALL_PATH}/lib")
#LINK_DIRECTORIES(${OpenCV_LIB_DIR})
#set(OpenCV_LIBS
#    opencv_core
#    opencv_imgproc
#    opencv_calib3d
#    opencv_video
#    opencv_features2d
#    opencv_ml
#    opencv_highgui
#    opencv_objdetect
##    opencv_contrib
##    opencv_legacy
##    opencv_gpu
#    )

#find_package(OpenCV REQUIRED PATHS ${OpenCV_DIR} NO_DEFAULT_PATH)

#find_package(OpenCV REQUIRED
#    core
#    imgproc
#    imgcodecs
##    highgui
#    )

find_package( OpenCV REQUIRED )

message(STATUS "OpenCV library status:")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")
message(STATUS "     path: ${OpenCV_INSTALL_PATH}")

include_directories(${OpenCV_INCLUDE_DIRS})

target_include_directories(${PROJECT_NAME}
    PUBLIC
    include/
    ${OpenCV_INCLUDE_DIRS}
    )
target_link_libraries( ${PROJECT_NAME}
        ${Boost_LIBRARIES}
        ${OpenCV_LIBS}
        pthread
        )


