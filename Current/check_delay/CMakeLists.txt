cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 17)

project(delay_find)
message(STATUS "")
message(STATUS "-------------------------------- CMAKE BEGINING for project ${PROJECT_NAME}")

# Тип корреляции при template matching для USE_CORR_TYPE:
# CORR_TYPE = 0 : Работа на CPU: OpenCV CCOEFF_NORMED (NO_GPU)
# CORR_TYPE = 2 : SQDIFF_NORMED (Прямая корреляция)
# CORR_TYPE = 6 : CCOEFF_NORMED  (Кросскорреляция модифицированная)
# CORR_TYPE = 8 ; COMBINED (объединение прямой и модифицированной кросскорреляции)
set(USE_CORR_TYPE 6)

# Использование в режиме GUI show_ok=0 -- удобство GUI при средней скорости.
set(USE_SHOW_OK0 0)
# Использовавть внешние колонки
set(USE_SPEAKER 1)

# Работа в режиме GUI (медленно), или без GUI (быстро):
set(USE_GUI 1)
# Использование логгера
set(USE_LOGGER 1)
# Режим цветового пространства, получаемых изображений от источника видеопотока
set(USE_COLOR_CHANNEL_MODE 8UC1) # (8UC3 -- BGR, 8UC1 -- GRAY8, 8UC4 -- RGBA)

set(USE_ROI_TMP 0) # Работа в ROI и с центральным шаблоном.

# Use Devices
set(USE_FOLDER_READER 1)
set(USE_VIDEO_READER 1)
set(USE_WEB_CAMERA 0)
set(USE_COLIBRI_TV 0)
set(USE_RASPBERRY_HQ_CAMERA 0)
set(USE_IMX219_CAMERA_MIPI 0)
set(USE_IMX477_SQUARE_CAMERA_MIPI 1)
set(USE_SHARED_MEMORY 0)
set(USE_ETHERNET_CONNECTION 0)
set(USE_PCAP 0)
set(USE_HIKVISION 1)

set(OpenCV_DIR $ENV{HOME}/opencv/install_4_7_0_contrib_cuda)

set(USE_CUDA_RESIZE_DEVICE_IMX219 0) # использование resize через cv::cuda на уровне device
set(SYSTEM_ENDIANNESS LITTLE) # системный порядок байтов LITTLE / BIG (зачастую LITTLE).

# Использование версии Yolo v3, v4 или trt:
set(USE_YOLO_VERSION trt)

# Использование GPU (1):
set(USE_GPU 1)

set(YOLO_LIB_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/../../darknet4)
set(TKDNN_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/../../tkDNN)
#################################################################################################

if(${USE_GPU} EQUAL 1)
   set(GPU_PREFIX gpu)
   add_definitions(-DUSE_GPU)
   message(STATUS "--------------------------- USE_GPU")
else()
   set(GPU_PREFIX cpu)
   message(STATUS "--------------------------- USE_CPU")
endif()

if(${USE_YOLO_VERSION} STREQUAL v3 OR ${USE_YOLO_VERSION} STREQUAL v4)
    set(YOLO_LIB -ldarknet_${GPU_PREFIX}_${USE_YOLO_VERSION})
elseif(${USE_YOLO_VERSION} STREQUAL trt)
    set(YOLO_LIB -ltkdnn_yolo)
endif()

set(CMAKE_MAKE_PROGRAM "make -j${nproc}") # Число потоков компиляции.
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/run) # директория сборки проекта
link_directories(${TKDNN_DIRECTORY})
link_directories(${YOLO_LIB_DIRECTORY})
add_definitions(-DYOLO_${USE_YOLO_VERSION})
message(STATUS "--------------------------- USE_YOLO_${USE_YOLO_VERSION}")

set(LIST_VALID_COLOR_CHANNEL_MODES 8UC1 8UC2 8UC3 8UC4)

if(NOT ${USE_COLOR_CHANNEL_MODE} IN_LIST LIST_VALID_COLOR_CHANNEL_MODES)
    message("Note: valid COLOR_CHANNEL_MODE list: " "${LIST_VALID_COLOR_CHANNEL_MODES}")
    message(FATAL_ERROR "Error: not recognize \"COLOR_CHANNEL_MODE\" mode = \"${USE_COLOR_CHANNEL_MODE}\"")
else()
    message(STATUS "USE_COLOR_CHANNEL_MODE = ${USE_COLOR_CHANNEL_MODE}")
    add_definitions(-DCCM_${USE_COLOR_CHANNEL_MODE})
endif()

if(${USE_CORR_TYPE})
    set(trac_lib_name -l_trac_tmml_${USE_CORR_TYPE}) # Название подключаемой библиотеки CUDA
    add_definitions(-DUSE_CUDA)
    message(STATUS "--------------------------- USE_CORR_TYPE=${USE_CORR_TYPE}")
    message(STATUS "--------------------------- USE_CUDA=1")    
    if(${USE_CORR_TYPE} EQUAL 10)
        add_definitions(-DTKDNN)
        message(STATUS "--------------------------- USE_TKDNN")
    endif()
else()
    set(trac_lib_name -l_trac_tmml_${USE_CORR_TYPE}) # Название подключаемой библиотеки CPU
    message(STATUS "--------------------------- USE_CORR_TYPE=${USE_CORR_TYPE}")
    message(STATUS "--------------------------- USE_CUDA=0")
endif()

if(${USE_ROI_TMP} EQUAL 1)
    add_definitions(-DUSE_ROI_TMP)
endif()

if(${USE_GUI} EQUAL 1)
    add_definitions(-DGUI_OK)
    message(STATUS "--------------------------- USE_GUI=1")
else()
    set(SHOW_PSTFX )
    message(STATUS "--------------------------- USE_GUI=0")
endif()

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})
link_directories(${CMAKE_CURRENT_LIST_DIR})

find_package(OpenCV REQUIRED PATHS ${OpenCV_DIR} NO_DEFAULT_PATH)
message(OpenCV_INCLUDE_DIRS=${OpenCV_INCLUDE_DIRS})
include_directories(${OpenCV_INCLUDE_DIRS})

link_directories(${CMAKE_CURRENT_LIST_DIR}/lib)

include_directories(tools/)

file(GLOB TracShatsFiles "${CMAKE_CURRENT_LIST_DIR}/tracshats/*")

add_executable(${PROJECT_NAME}
    tracking.ini
    main.cpp
    application.cpp
    application.hpp
    tools/plot/plot.cpp
    tools/plot/plot.hpp
    ##############  Trackers ###################################################
    ${TracShatsFiles}    
    ##############  Tools  ####################################################
    tools/INIReader.h
    tools/ExtendINIReader.hpp
    tools/watchdog.h
    tools/colors.h
    tools/toolbox_common_utils/toolbox_common_utils.cpp
    tools/toolbox_common_utils/toolbox_common_utils.hpp

    tools/recorder/recorder.hpp
    tools/recorder/recorder.cpp
    
    tools/time_keeper/time_keeper.cpp
    tools/time_keeper/time_keeper.hpp

    tools/temperature_monitor/temperature_monitor.cpp
    tools/temperature_monitor/temperature_monitor.hpp

    tools/custom_filesystem/custom_filesystem.hpp # TODO: переименовать path_utils или files_os_tools/utils
    tools/custom_filesystem/custom_filesystem.cpp

    ################### Devices ################
    devices/device.cpp
    devices/device.hpp
    devices/iframehandler.cpp
    devices/iframehandler.h
    devices/icommandhandler.h)

    if(${USE_LOGGER} EQUAL 1)
        add_definitions(-DUSE_LOGGER)
        target_sources(${PROJECT_NAME} PRIVATE
            logger/logger.cpp
            logger/logger.hpp
            logger/factory.cpp
            logger/factory.h
            logger/settings.hpp)
    endif()

if(${USE_RASPBERRY_HQ_CAMERA} EQUAL 1)
    find_package(PkgConfig REQUIRED)
    pkg_search_module(GST REQUIRED gstreamer-1.0>=1.4
        gstreamer-sdp-1.0>=1.4
        gstreamer-video-1.0>=1.4
        gstreamer-app-1.0>=1.4
        )
endif()

if(${USE_FOLDER_READER} EQUAL 1)
    add_definitions(-DUSE_FOLDER_READER)
    target_sources(${PROJECT_NAME} PRIVATE
        devices/FolderReader/folderreader.h
        devices/FolderReader/folderreader.cpp
    )
endif()

if(${USE_VIDEO_READER} EQUAL 1)
    add_definitions(-DUSE_VIDEO_READER)
    target_sources(${PROJECT_NAME} PRIVATE
        devices/VideoReader/videoreader.h
        devices/VideoReader/videoreader.cpp
    )
endif()

if(${USE_WEB_CAMERA} EQUAL 1)
    add_definitions(-DUSE_WEB_CAMERA)
    target_sources(${PROJECT_NAME} PRIVATE
        devices/WebCamera/webcamera.hpp
        devices/WebCamera/webcamera.cpp
    )
endif()

if(${USE_COLIBRI_TV} EQUAL 1)
    add_definitions(-DUSE_COLIBRI_TV)
    set(USE_ETHERNET_CONNECTION 1)
    target_sources(${PROJECT_NAME} PRIVATE
        devices/colibritv/colibritv.cpp
        devices/colibritv/colibritv.h
        devices/colibritv/eth/colibritvclient.cpp
        devices/colibritv/eth/colibritvclient.h
        devices/colibritv/eth/colibritv_ethcontroller.cpp
        devices/colibritv/eth/colibritv_ethcontroller.h
        devices/colibritv/eth/colibritvserver.cpp
        devices/colibritv/eth/colibritvserver.h
    )
endif()

if(${USE_RASPBERRY_HQ_CAMERA} EQUAL 1)
    add_definitions(-DUSE_RASPBERRY_HQ_CAMERA)
    target_sources(${PROJECT_NAME} PRIVATE
        devices/RaspberryHQCamera/raspberryhqcamera.cpp
        devices/RaspberryHQCamera/raspberryhqcamera.hpp
        devices/RaspberryHQCamera/factory.cpp
        devices/RaspberryHQCamera/factory.hpp
        devices/RaspberryHQCamera/settings.hpp
    )
    target_link_libraries(${PROJECT_NAME} ${GST_LIBRARIES} gstapp-1.0)
    target_include_directories(${PROJECT_NAME} PRIVATE ${GST_INCLUDE_DIRS})
endif()

if(${USE_IMX219_CAMERA_MIPI} EQUAL 1)
    add_definitions(-DUSE_IMX219_CAMERA_MIPI)
    target_sources(${PROJECT_NAME} PRIVATE
        devices/IMX219CameraMIPI/imx219_camera_mipi_factory.hpp
        devices/IMX219CameraMIPI/imx219_camera_mipi_factory.cpp
        devices/IMX219CameraMIPI/imx219_camera_mipi.hpp
        devices/IMX219CameraMIPI/imx219_camera_mipi.cpp
        devices/IMX219CameraMIPI/camera_settings.hpp
    )
    if(${USE_CUDA_RESIZE_DEVICE_IMX219} EQUAL 1)
        add_definitions(-DUSE_CUDA_RESIZE_DEVICE_IMX219)
    endif()
endif()

if(${USE_IMX477_SQUARE_CAMERA_MIPI} EQUAL 1)
    add_definitions(-DUSE_IMX477_SQUARE_CAMERA_MIPI)
    target_sources(${PROJECT_NAME} PRIVATE
        devices/imx477squareCameraMIPI/imx477_square_camera_mipi_factory.hpp
        devices/imx477squareCameraMIPI/imx477_square_camera_mipi_factory.cpp
        devices/imx477squareCameraMIPI/imx477_square_camera_mipi.hpp
        devices/imx477squareCameraMIPI/imx477_square_camera_mipi.cpp
        devices/imx477squareCameraMIPI/imx477_square_camera_mipi_settings.hpp
    )
endif()

if(${USE_HIKVISION} EQUAL 1)
    add_definitions(-DUSE_HIKVISION)
    include_directories(tools/)
    include_directories(tools/toolbox_common_utils/)
    target_sources(${PROJECT_NAME} PRIVATE
        devices/EthCameraRtsp/rtsp_h265_device.hpp
        devices/EthCameraRtsp/rtsp_h265_device.cpp
        devices/EthCameraRtsp/rtsp_h265_device_factory.hpp
        devices/EthCameraRtsp/rtsp_h265_device_factory.cpp
        devices/EthCameraRtsp/rtsp_h265_device_settings.hpp
        devices/led.cpp
        )
    find_package(PkgConfig REQUIRED)
    pkg_search_module(GST REQUIRED gstreamer-1.0>=1.4
        gstreamer-sdp-1.0>=1.4
        gstreamer-video-1.0>=1.4
        gstreamer-app-1.0>=1.4
        gstrtp-1.0
        glib-2.0
        )
    target_link_libraries(${PROJECT_NAME} ${GST_LIBRARIES} ${GST_LIBRARIES} gstapp-1.0)
    target_include_directories(${PROJECT_NAME} PRIVATE ${GST_INCLUDE_DIRS})

endif()


if(${USE_SHARED_MEMORY} EQUAL 1)
    add_definitions(-DUSE_SHARED_MEMORY)
    target_sources(${PROJECT_NAME} PRIVATE
        devices/SharedMemory/sharedmemory.cpp
        devices/SharedMemory/sharedmemory.hpp
        devices/SharedMemory/ipc/shared_memory.cpp
        devices/SharedMemory/ipc/shared_memory.h

        devices/SharedMemory/eth/sharedmemory_ethernetcontroller.cpp
        devices/SharedMemory/eth/sharedmemory_ethernetcontroller.h
        devices/SharedMemory/eth/sharedmemoryclient.cpp
        devices/SharedMemory/eth/sharedmemoryclient.hpp
        devices/SharedMemory/eth/sharedmemoryserver.cpp
        devices/SharedMemory/eth/sharedmemoryserver.hpp

        devices/SharedMemory/cmd/sharedmemory_cmdmanager.cpp
        devices/SharedMemory/cmd/sharedmemory_cmdmanager.hpp
    )
    target_link_libraries(${PROJECT_NAME} -lrt)
endif()


if(${USE_ETHERNET_CONNECTION} EQUAL 1)
    add_definitions(-DUSE_ETHERNET_CONNECTION)
    target_sources(${PROJECT_NAME} PRIVATE
        eth/ethcontroller.cpp
        eth/ethcontroller.h
        eth/server.cpp
        eth/server.h
        eth/client.cpp
        eth/client.h

        eth/socket/tcpclient.cpp
        eth/socket/tcpsocket.h
        eth/socket/udpsocket.cpp
        eth/socket/socketaddress.cpp
        eth/socket/tcpclient.h
        eth/socket/udpclient.cpp
        eth/socket/udpsocket.h
        eth/socket/socketaddress.h
        eth/socket/tcpserver.cpp
        eth/socket/udpclient.h
        eth/socket/socket.cpp
        eth/socket/tcpserver.h
        eth/socket/udpserver.cpp
        eth/socket/socket.h
        eth/socket/tcpsocket.cpp
        eth/socket/udpserver.h

        cmd/cmdmanager.cpp
        cmd/cmdmanager.h
    )

    if(${USE_PCAP} EQUAL 1)
        add_definitions(-DPCAP)
        target_sources(${PROJECT_NAME} PRIVATE
            eth/socket/pcapclient.cpp
            eth/socket/pcapsocket.h
            eth/socket/pcapclient.h
            eth/socket/pcapserver.cpp
            eth/socket/pcapserver.h
            eth/socket/pcapsocket.cpp
        )
        target_link_libraries(${PROJECT_NAME} -lpcap)
    endif()


endif()

if(${USE_GUI} EQUAL 0)
    set(GUI_RUN_PSTFX "notgui")
elseif(${USE_GUI} EQUAL 1)
    set(GUI_RUN_PSTFX "gui")
else()
    message(FATAL_ERROR "Error: incorrect \"USE_GUI\" parameter = \"#{USE_GUI}\"")
endif()

#                     gui/notgui    8UC1/8UC2/8UC3/16FC1 etc..
set(run_name run_${GUI_RUN_PSTFX}_${USE_COLOR_CHANNEL_MODE}_${USE_CORR_TYPE})

#target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} -lrt ${trac_lib_name} -lpthread)
#set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${run_name})

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} ${YOLO_LIB} ${trac_lib_name} -lrt -lpthread)
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} ${YOLO_LIB} ${trac_lib_name} -lrt -lpthread)
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${run_name})

