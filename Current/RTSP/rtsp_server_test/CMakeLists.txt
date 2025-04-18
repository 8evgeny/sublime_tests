cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 17)

project(test_RTSP_server)
message(STATUS "")
message(STATUS "-------------------------------- CMAKE BEGINING for project ${CMAKE_PROJECT_NAME}")

# Использование GPU:
set(USE_GPU 2) # (0 - CPU, 1 - CUDA, 2 - OPENCL)


set(OpenCV_DIR $ENV{HOME}/opencv/install_4_7_0_contrib_cuda)
set(USE_RTSP_SERVER 1)
#################################################################################################

# Использование в режиме GUI show_ok=0 -- удобство GUI при средней скорости.
set(USE_SHOW_OK0 0)
# Использовавть внешние колонки
set(USE_SPEAKER 1)

# Работа в режиме GUI (медленно), или без GUI (быстро):
set(USE_GUI 1)
# Использование логгера
set(USE_LOGGER 1)
# Режим цветового пространства, получаемых изображений от источника видеопотока
set(USE_COLOR_CHANNEL_MODE 8UC3) # (8UC3 -- BGR, 8UC1 -- GRAY8, 8UC4 -- RGBA)

set(USE_ROI_TMP 0) # Работа в ROI и с центральным шаблоном.
# Use Devices:
set(USE_FOLDER_READER 1) # 0
set(USE_VIDEO_READER 0) # 1
set(USE_WEB_CAMERA 1) # 2
set(USE_COLIBRI_TV 0) # 3
set(USE_RASPBERRY_HQ_CAMERA 0) # 4
set(USE_IMX477_SQUARE_CAMERA_MIPI 1) # 5
set(USE_IMX219_CAMERA_MIPI 0) # 6
set(USE_HIKVISION 1) # 7
set(USE_SHARED_MEMORY 0) # 8
set(USE_HVGS_GRAY_USB_CAMERA 0) # 9
set(USE_CORSAIR_400_RAW 0) # 10 (Шар ОЭЦН400, сырой UDP видеопоток напрямую)
set(USE_ETHERNET_CONNECTION 0)
set(USE_PCAP 0)
set(USE_GST_RTP 0)

set(USE_CUDA_RESIZE_DEVICE_IMX219 0) # использование resize через cv::cuda на уровне device
set(SYSTEM_ENDIANNESS LITTLE) # системный порядок байтов LITTLE / BIG (зачастую LITTLE).

if(${USE_CORSAIR_400_RAW} EQUAL 1)
    set(DBG_VIDEO_SENDER 0) # включение отправки видео и командного обмена с эмулятором шара (QtProg/poes400/corsair_terminal_emulator)
    # Используем программу в паре с терминалкой 400-го, раздел ini-файла [vtrack_data_sender], подключаем библиотеку vtrack_data_sender
    set(USE_DBG_SEND_VTRACK 0) # дополнителоное логирование отладочной информации в процессе отправки рамок целей
endif() #     if(${USE_CORSAIR_400_RAW} EQUAL 1)

#################################################################################################

if(${USE_GPU} EQUAL 0)
    set(GPU_PREFIX cpu)
    message(STATUS "--------------------------- USE_CPU")
endif() # END if(${USE_GPU} EQUAL 0)


set(CMAKE_MAKE_PROGRAM "make -j${nproc}") # Число потоков компиляции.
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/run) # директория сборки проекта
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/lib_modules)

set(LIST_VALID_COLOR_CHANNEL_MODES 8UC1 8UC2 8UC3 8UC4)

if(NOT ${USE_COLOR_CHANNEL_MODE} IN_LIST LIST_VALID_COLOR_CHANNEL_MODES)
    message("Note: valid COLOR_CHANNEL_MODE list: " "${LIST_VALID_COLOR_CHANNEL_MODES}")
    message(FATAL_ERROR "Error: not recognize \"COLOR_CHANNEL_MODE\" mode = \"${USE_COLOR_CHANNEL_MODE}\"")
else()
    message(STATUS "USE_COLOR_CHANNEL_MODE = ${USE_COLOR_CHANNEL_MODE}")
    add_definitions(-DCCM_${USE_COLOR_CHANNEL_MODE})
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

link_directories(${CMAKE_CURRENT_LIST_DIR})

find_package(OpenCV REQUIRED PATHS ${OpenCV_DIR} NO_DEFAULT_PATH)
message(OpenCV_INCLUDE_DIRS=${OpenCV_INCLUDE_DIRS})
include_directories(${OpenCV_INCLUDE_DIRS})

link_directories(${CMAKE_CURRENT_LIST_DIR}/lib)

include_directories(tools/)

add_executable(${CMAKE_PROJECT_NAME}
    tracking.ini
    main.cpp
    application.cpp
    application.hpp
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
    tools/custom_filesystem/custom_filesystem.hpp # переименовать path_utils или files_os_tools/utils
    tools/custom_filesystem/custom_filesystem.cpp
    ################### Devices ################
    devices/device.cpp
    devices/device.hpp
    devices/iframehandler.cpp
    devices/iframehandler.h
    devices/icommandhandler.h
    )

if(${USE_LOGGER} EQUAL 1)
    add_definitions(-DUSE_LOGGER)
    target_sources(${CMAKE_PROJECT_NAME} PRIVATE
        logger/logger.cpp
        logger/logger.hpp
        logger/factory.cpp
        logger/factory.h
        logger/settings.hpp)
endif() # END if(${USE_LOGGER} EQUAL 1)

########################### BEGIN DEVICES:

if(${USE_FOLDER_READER} EQUAL 1) # 0
    add_definitions(-DUSE_FOLDER_READER)
    target_sources(${CMAKE_PROJECT_NAME} PRIVATE
        devices/FolderReader/folderreader.h
        devices/FolderReader/folderreader.cpp
        )
endif() # END if(${USE_FOLDER_READER} EQUAL 1)

if(${USE_VIDEO_READER} EQUAL 1) # 1
    add_definitions(-DUSE_VIDEO_READER)
    target_sources(${CMAKE_PROJECT_NAME} PRIVATE
        devices/VideoReader/videoreader.h
        devices/VideoReader/videoreader.cpp
        )
endif() # END if(${USE_VIDEO_READER} EQUAL 1)

if(${USE_WEB_CAMERA} EQUAL 1) # 2
    add_definitions(-DUSE_WEB_CAMERA)
    target_sources(${CMAKE_PROJECT_NAME} PRIVATE
        devices/WebCamera/webcamera.hpp
        devices/WebCamera/webcamera.cpp
        )
endif() # END if(${USE_WEB_CAMERA} EQUAL 1)

if(${USE_COLIBRI_TV} EQUAL 1) # 3
    add_definitions(-DUSE_COLIBRI_TV)
    set(USE_ETHERNET_CONNECTION 1)
    target_sources(${CMAKE_PROJECT_NAME} PRIVATE
        devices/colibritv/colibritv.cpp
        devices/colibritv/colibritv.h
        devices/colibritv/eth/colibritvclient.cpp
        devices/colibritv/eth/colibritvclient.h
        devices/colibritv/eth/colibritv_ethcontroller.cpp
        devices/colibritv/eth/colibritv_ethcontroller.h
        devices/colibritv/eth/colibritvserver.cpp
        devices/colibritv/eth/colibritvserver.h
        )
endif() # END if(${USE_COLIBRI_TV} EQUAL 1)

if(${USE_RASPBERRY_HQ_CAMERA} EQUAL 1) # 4
    find_package(PkgConfig REQUIRED)
    pkg_search_module(GST REQUIRED gstreamer-1.0>=1.4
        gstreamer-sdp-1.0>=1.4
        gstreamer-video-1.0>=1.4
        gstreamer-app-1.0>=1.4
        )
    add_definitions(-DUSE_RASPBERRY_HQ_CAMERA)
    target_sources(${CMAKE_PROJECT_NAME} PRIVATE
        devices/RaspberryHQCamera/raspberryhqcamera.cpp
        devices/RaspberryHQCamera/raspberryhqcamera.hpp
        devices/RaspberryHQCamera/factory.cpp
        devices/RaspberryHQCamera/factory.hpp
        devices/RaspberryHQCamera/settings.hpp
        )
    target_link_libraries(${CMAKE_PROJECT_NAME} ${GST_LIBRARIES} gstapp-1.0)
    target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${GST_INCLUDE_DIRS})
endif() # END if(${USE_RASPBERRY_HQ_CAMERA} EQUAL 1)

if(${USE_IMX477_SQUARE_CAMERA_MIPI} EQUAL 1) # 5
    add_definitions(-DUSE_IMX477_SQUARE_CAMERA_MIPI)
    target_sources(${CMAKE_PROJECT_NAME} PRIVATE
        devices/imx477squareCameraMIPI/imx477_square_camera_mipi_factory.hpp
        devices/imx477squareCameraMIPI/imx477_square_camera_mipi_factory.cpp
        devices/imx477squareCameraMIPI/imx477_square_camera_mipi.hpp
        devices/imx477squareCameraMIPI/imx477_square_camera_mipi.cpp
        devices/imx477squareCameraMIPI/imx477_square_camera_mipi_settings.hpp
        )
endif() # END if(${USE_IMX477_SQUARE_CAMERA_MIPI} EQUAL 1)

if(${USE_IMX219_CAMERA_MIPI} EQUAL 1) # 6
    add_definitions(-DUSE_IMX219_CAMERA_MIPI)
    target_sources(${CMAKE_PROJECT_NAME} PRIVATE
        devices/IMX219CameraMIPI/imx219_camera_mipi_factory.hpp
        devices/IMX219CameraMIPI/imx219_camera_mipi_factory.cpp
        devices/IMX219CameraMIPI/imx219_camera_mipi.hpp
        devices/IMX219CameraMIPI/imx219_camera_mipi.cpp
        devices/IMX219CameraMIPI/camera_settings.hpp
        )
    if(${USE_CUDA_RESIZE_DEVICE_IMX219} EQUAL 1)
        add_definitions(-DUSE_CUDA_RESIZE_DEVICE_IMX219)
    endif() # END if(${USE_CUDA_RESIZE_DEVICE_IMX219} EQUAL 1)
endif() # END if(${USE_IMX219_CAMERA_MIPI} EQUAL 1)

if(${USE_GST_RTP})
    add_definitions(-DUSE_GST_RTP)
    include_directories(tools/)
    include_directories(tools/toolbox_common_utils/)
    target_sources(
        ${CMAKE_PROJECT_NAME} PRIVATE
        devices/GstRtp/gst_rtp.hpp
        devices/GstRtp/gst_rtp.cpp
        devices/GstRtp/gst_rtp_factory.hpp
        devices/GstRtp/gst_rtp_factory.cpp
        devices/GstRtp/gst_rtp_settings.hpp
        )
endif() # END if(${USE_GST_RTP})

if(${USE_HIKVISION} EQUAL 1) # 7
    add_definitions(-DUSE_HIKVISION)
    include_directories(tools/)
    include_directories(tools/toolbox_common_utils/)
    target_sources(${CMAKE_PROJECT_NAME} PRIVATE
        devices/EthCameraRtsp/rtsp_h265_device.hpp
        devices/EthCameraRtsp/rtsp_h265_device.cpp
        devices/EthCameraRtsp/rtsp_h265_device_factory.hpp
        devices/EthCameraRtsp/rtsp_h265_device_factory.cpp
        devices/EthCameraRtsp/rtsp_h265_device_settings.hpp
        )
    find_package(PkgConfig REQUIRED)
    pkg_search_module(GST REQUIRED gstreamer-1.0>=1.4
        gstreamer-sdp-1.0>=1.4
        gstreamer-video-1.0>=1.4
        gstreamer-app-1.0>=1.4
        gstrtp-1.0
        glib-2.0
        )
    target_link_libraries(${CMAKE_PROJECT_NAME} ${GST_LIBRARIES} ${GST_LIBRARIES} gstapp-1.0)
    target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${GST_INCLUDE_DIRS})
endif() # END if(${USE_HIKVISION} EQUAL 1)

if(${USE_SHARED_MEMORY} EQUAL 1) # 8
    add_definitions(-DUSE_SHARED_MEMORY)
    target_sources(${CMAKE_PROJECT_NAME} PRIVATE
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
    target_link_libraries(${CMAKE_PROJECT_NAME} -lrt)
endif() # END if(${USE_SHARED_MEMORY} EQUAL 1)

if(${USE_HVGS_GRAY_USB_CAMERA} EQUAL 1) # 9
    add_definitions(-DUSE_HVGS_GRAY_USB_CAMERA)
    target_sources(devices PRIVATE
        devices/HVGS_GRAY_USB_Camera/hvgs_gray_usb_camera.hpp
        devices/HVGS_GRAY_USB_Camera/hvgs_gray_usb_camera.cpp
        devices/HVGS_GRAY_USB_Camera/hvgs_gray_usb_camera_factory.hpp
        devices/HVGS_GRAY_USB_Camera/hvgs_gray_usb_camera_factory.cpp
        devices/HVGS_GRAY_USB_Camera/hvgs_gray_usb_camera_settings.hpp
        tools/ExtendINIReader.hpp
        )
    add_library(lib_hvgs_camera SHARED IMPORTED)
    set_target_properties(lib_hvgs_camera PROPERTIES
        IMPORTED_LOCATION "/usr/lib/libMVSDK.so")
    target_link_libraries(devices lib_hvgs_camera)
endif() # END if(${USE_HVGS_GRAY_USB_CAMERA} EQUAL 1)

if(${USE_CORSAIR_400_RAW} EQUAL 1) # 10
    add_definitions(-DUSE_CORSAIR_400_RAW)
    set(cors400_device_dir_path "${CMAKE_CURRENT_LIST_DIR}/devices/Corsair400raw/")
    set(cors400_src_dir_path "${cors400_device_dir_path}/eth/")
    target_sources(${CMAKE_PROJECT_NAME} PRIVATE
        ### device ###
        ${cors400_device_dir_path}/corsair400raw.hpp
        ${cors400_device_dir_path}/corsair400raw.cpp
        ${cors400_device_dir_path}/corsair400raw_factory.cpp
        ${cors400_device_dir_path}/corsair400raw_factory.hpp
        ${cors400_device_dir_path}/corsair400raw_settings.hpp
        ### corsair 400 eth platform ###
        #### base ####
        ${cors400_src_dir_path}/base/BaseThread.hpp
        ${cors400_src_dir_path}/base/BaseThread.cpp
        ${cors400_src_dir_path}/base/Socket.hpp
        ${cors400_src_dir_path}/base/Socket.cpp
        ${cors400_src_dir_path}/base/SocketAddress.hpp
        ${cors400_src_dir_path}/base/SocketAddress.cpp
        ${cors400_src_dir_path}/base/TripleBuffer.hpp
        ${cors400_src_dir_path}/base/TripleBuffer.cpp
        #### protocols ####
        ##### udp #####
        ${cors400_src_dir_path}/protocols/udp/UDPClient.hpp
        ${cors400_src_dir_path}/protocols/udp/UDPClient.cpp
        ${cors400_src_dir_path}/protocols/udp/UDPServer.hpp
        ${cors400_src_dir_path}/protocols/udp/UDPServer.cpp
        ${cors400_src_dir_path}/protocols/udp/UDPSocket.hpp
        ${cors400_src_dir_path}/protocols/udp/UDPSocket.cpp
        #### global ####
        ${cors400_src_dir_path}/EthGlobal.hpp
        #### servers ####
        ${cors400_src_dir_path}/servers/RAWVideoServer.hpp
        ${cors400_src_dir_path}/servers/RAWVideoServer.cpp
        ${cors400_src_dir_path}/servers/DataServer.hpp
        ${cors400_src_dir_path}/servers/DataServer.cpp
        ) # END target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    include_directories(
        ${cors400_device_dir_path}/
        ${cors400_src_dir_path}/
        ${cors400_src_dir_path}/base/
        ${cors400_src_dir_path}/protocols/udp/
        )
endif() # END if(${USE_CORSAIR_400_RAW} EQUAL 1)

############################################ END DEVICES

if(${USE_ETHERNET_CONNECTION} EQUAL 1)
    add_definitions(-DUSE_ETHERNET_CONNECTION)
    target_sources(${CMAKE_PROJECT_NAME} PRIVATE
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
        target_sources(${CMAKE_PROJECT_NAME} PRIVATE
            eth/socket/pcapclient.cpp
            eth/socket/pcapsocket.h
            eth/socket/pcapclient.h
            eth/socket/pcapserver.cpp
            eth/socket/pcapserver.h
            eth/socket/pcapsocket.cpp
            )
        target_link_libraries(${CMAKE_PROJECT_NAME} -lpcap)
    endif() # END if(${USE_PCAP} EQUAL 1)
endif() # END if(${USE_ETHERNET_CONNECTION} EQUAL 1)

if(${USE_CORSAIR_400_RAW} EQUAL 1)
    add_definitions(-USE_CORSAIR_400_RAW)
    if(${USE_DBG_SEND_VTRACK} EQUAL 1)
        add_definitions(-DUSE_DBG_SEND_VTRACK)
    endif() # END if(${USE_DBG_SEND_VTRACK} EQUAL 1)

    if(${DBG_VIDEO_SENDER} EQUAL 1)
        add_definitions(-DDBG_VIDEO_SENDER)
    endif() # END if(${DBG_VIDEO_SENDER} EQUAL 1)

    add_library(vtrack_data_sender SHARED
        modules/vtrack_data_sender/vtrack_data_struct.hpp
        modules/vtrack_data_sender/vtrack_data_sender.hpp
        modules/vtrack_data_sender/vtrack_data_sender.cpp
        modules/vtrack_data_sender/vtrack_data_sender_factory.hpp
        modules/vtrack_data_sender/vtrack_data_sender_factory.cpp
        )
    target_link_libraries(${CMAKE_PROJECT_NAME} vtrack_data_sender)

    add_subdirectory(modules/eth_controller_toolbox)
    include_directories(modules/eth_controller_toolbox/)

    add_library(cmd400_keeper SHARED
        modules/cmd400/cmd400_struct.hpp
        modules/cmd400/cmd400_keeper.hpp
        modules/cmd400/cmd400_keeper.cpp
        modules/cmd400/cmd400_keeper_factory.hpp
        modules/cmd400/cmd400_keeper_factory.cpp
        )
    target_link_libraries(${CMAKE_PROJECT_NAME} vtrack_data_sender cmd400_keeper eth_controller_toolbox_lib)

endif() # END if(${USE_CORSAIR_400_RAW} EQUAL 1)

if(${USE_RTSP_SERVER} EQUAL 1)
    add_definitions(-DUSE_RTSP_SERVER)
    find_package(PkgConfig REQUIRED)
    #find_package(GStreamer REQUIRED)
    pkg_search_module(GST REQUIRED gstreamer-1.0>=1.4
        gstreamer-sdp-1.0>=1.4
        gstreamer-video-1.0>=1.4
        gstreamer-app-1.0>=1.4
        gstreamer-rtp-1.0>=1.4
        gstreamer-rtsp-1.0>=1.4
        gstreamer-udp-1.0>=1.4
        gstreamer-h264-1.0>=1.4
        gstreamer-1.0
        gstreamer-webrtc-1.0
        gstreamer-pbutils-1.0
        gstreamer-check-1.0
        gstreamer-net-1.0>=1.4
        gstrtp-1.0
        glib-2.0
        gobject-2.0
        )

    pkg_search_module(GLIB REQUIRED IMPORTED_TARGET glib-2.0)
    pkg_search_module(gstreamer REQUIRED IMPORTED_TARGET gstreamer-1.0>=1.4)
    pkg_search_module(gstreamer_sdp REQUIRED IMPORTED_TARGET gstreamer-sdp-1.0>=1.4)
    pkg_search_module(gstreamer_app REQUIRED IMPORTED_TARGET gstreamer-app-1.0>=1.4)
    pkg_search_module(gstreamer_video REQUIRED IMPORTED_TARGET gstreamer-video-1.0>=1.4)
    pkg_search_module(gstreamer_rtp REQUIRED IMPORTED_TARGET gstreamer-rtp-1.0>=1.4)
    pkg_search_module(gstreamer_rtsp REQUIRED IMPORTED_TARGET gstreamer-rtp-1.0>=1.4)
    pkg_search_module(gstreamer_net REQUIRED IMPORTED_TARGET gstreamer-net-1.0>=1.4)

    include_directories(${GST_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS})

    list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
    list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
    include_directories("gst-rtsp-server")
    include_directories("${GLIB_INCLUDE_DIRS}")

    add_library(gst_rtsp_server SHARED
        gst-rtsp-server/gst/rtsp-server/rtsp-address-pool.h
        gst-rtsp-server/gst/rtsp-server/rtsp-auth.h
        gst-rtsp-server/gst/rtsp-server/rtsp-client.h
        gst-rtsp-server/gst/rtsp-server/rtsp-context.h
        gst-rtsp-server/gst/rtsp-server/rtsp-media.h
        gst-rtsp-server/gst/rtsp-server/rtsp-media-factory.h
        gst-rtsp-server/gst/rtsp-server/rtsp-media-factory-uri.h
        gst-rtsp-server/gst/rtsp-server/rtsp-mount-points.h
        gst-rtsp-server/gst/rtsp-server/rtsp-params.h
        gst-rtsp-server/gst/rtsp-server/rtsp-permissions.h
        gst-rtsp-server/gst/rtsp-server/rtsp-sdp.h
        gst-rtsp-server/gst/rtsp-server/rtsp-server.h
        gst-rtsp-server/gst/rtsp-server/rtsp-session.h
        gst-rtsp-server/gst/rtsp-server/rtsp-session-media.h
        gst-rtsp-server/gst/rtsp-server/rtsp-session-pool.h
        gst-rtsp-server/gst/rtsp-server/rtsp-stream.h
        gst-rtsp-server/gst/rtsp-server/rtsp-stream-transport.h
        gst-rtsp-server/gst/rtsp-server/rtsp-thread-pool.h
        gst-rtsp-server/gst/rtsp-server/rtsp-token.h
        gst-rtsp-server/gst/rtsp-server/rtsp-address-pool.c
        gst-rtsp-server/gst/rtsp-server/rtsp-media-factory-uri.c
        gst-rtsp-server/gst/rtsp-server/rtsp-params.c
        gst-rtsp-server/gst/rtsp-server/rtsp-session-media.c
        gst-rtsp-server/gst/rtsp-server/rtsp-auth.c
        gst-rtsp-server/gst/rtsp-server/rtsp-stream.c
        gst-rtsp-server/gst/rtsp-server/rtsp-media-factory.c
        gst-rtsp-server/gst/rtsp-server/rtsp-permissions.c
        gst-rtsp-server/gst/rtsp-server/rtsp-session-pool.c
        gst-rtsp-server/gst/rtsp-server/rtsp-thread-pool.c
        gst-rtsp-server/gst/rtsp-server/rtsp-client.c
        gst-rtsp-server/gst/rtsp-server/rtsp-media.c
        gst-rtsp-server/gst/rtsp-server/rtsp-sdp.c
        gst-rtsp-server/gst/rtsp-server/rtsp-session.c
        gst-rtsp-server/gst/rtsp-server/rtsp-token.c
        gst-rtsp-server/gst/rtsp-server/rtsp-context.c
        gst-rtsp-server/gst/rtsp-server/rtsp-mount-points.c
        gst-rtsp-server/gst/rtsp-server/rtsp-server.c
        gst-rtsp-server/gst/rtsp-server/rtsp-stream-transport.c
        )

    set(GSTREAMER_LIBS
        gstreamer-1.0
        gstbase-1.0
        gstrtp-1.0
        gstsdp-1.0
        gstrtsp-1.0
        gstapp-1.0
        gstnet-1.0
        gobject-2.0
        gmodule-2.0
        xml2
        gthread-2.0
        glib-2.0
        gio-2.0
        )
    target_link_libraries(gst_rtsp_server "${GSTREAMER_LIBS}")

    #get_directory_property(hasParent PARENT_DIRECTORY)

    if(hasParent)
        set(GST_RTSP_SERVER_INCLUDE_DIRS
            "${CMAKE_CURRENT_LIST_DIR}/gst-rtsp-server"
            "${GLIB_INCLUDE_DIRS}"
            "${GSTREAMER_INCLUDE_DIRS}"
            "${GSTREAMER_BASE_INCLUDE_DIRS}"
            "${GSTREAMER_RTSP_INCLUDE_DIRS}"
            PARENT_SCOPE
            )
    endif()


    add_library(rtsp_server SHARED
        myserver.hpp
        myserver.cpp
        )
    set_target_properties(rtsp_server PROPERTIES LINKER_LANGUAGE CXX)

    target_link_libraries(rtsp_server ${GST_LIBRARIES} ${OpenCV_LIBS} gst_rtsp_server -lrt -lpthread)
    target_link_libraries(${CMAKE_PROJECT_NAME} rtsp_server)
endif() # END if(${USE_RTSP_SERVER} EQUAL 1)


if(${USE_GUI} EQUAL 0)
    set(GUI_RUN_PSTFX "notgui")
elseif(${USE_GUI} EQUAL 1)
    set(GUI_RUN_PSTFX "gui")
else()
    message(FATAL_ERROR "Error: incorrect \"USE_GUI\" parameter = \"#{USE_GUI}\"")
    endif() # END if(NOT ${USE_GUI} EQUAL 0)

    set(run_name run_${GUI_RUN_PSTFX}_${USE_COLOR_CHANNEL_MODE})

    target_link_libraries(${CMAKE_PROJECT_NAME} ${OpenCV_LIBS} ${GPU_LIB} ${trac_lib_name} -lrt -lpthread)
    target_link_libraries(${CMAKE_PROJECT_NAME} ${OpenCV_LIBS} ${GPU_LIB} ${trac_lib_name} -lrt -lpthread)
    set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES OUTPUT_NAME ${run_name})
