cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 17)

project(chain_drone_server)
message(STATUS "")
message(STATUS "-------------------------------- CMAKE BEGINING for project chain_drone_server")

# Работа в режиме GUI (медленно), или без GUI (быстро):
set(USE_DBG 0)
set(USE_GUI 0)
# Использование логгера
set(USE_LOGGER 1)
set(USE_ETH_MD 1)
# Режим цветового пространства, получаемых изображений от источника видеопотока
set(USE_COLOR_CHANNEL_MODE 8UC1) # (8UC3 -- BGR, 8UC1 -- GRAY8, 8UC4 -- RGBA)
# Тип корреляции при template matching for USE_CORR_TYPE
# CORR_TYPE = 0  : CPU_TRACKER
# CORR_TYPE = 2  : SQDIFF_NORMED
# CORR_TYPE = 6  : CCOEFF_NORMED
# CORR_TYPE = 8 : COMBINED (объединение прямой и модифицированной кросскорреляции)
# CORR_TYPE = 10 : TKDNN
set(USE_CORR_TYPE 8)
add_definitions(-DCORR_TYPE=${USE_CORR_TYPE})
add_definitions(-DCCM_8UC1)
set(USE_RECORDER 1) # Запись видеопотока в директторию

#FENIX2 ethernet
set(USE_ETH_CONTROLLER 1) # использование Eth для приема/передачи фреймов и команд
set(ETH_RX_TX_FRAME_PROTOCOL RTP) # Доступны : TCPIP, RTP
set(USE_RX_TX_CMD 1) # использование приема/передачи команд
set(GST_API_TYPE 1) # 0 - CV_API, 1 - C_API_H264, 2 - C_API_H265, 3 - C_API_MPEG;
set(USE_TCP_SETUP 0) # 1 - отправляем тип трекера (и другие команды по желанию) при установке соединения с клиентом

# Use Devices
set(USE_FOLDER_READER 0)
set(USE_VIDEO_READER 0)
set(USE_WEB_CAMERA 1)
set(USE_RASPBERRY_HQ_CAMERA 0)
set(USE_IMX219_CAMERA_MIPI 0)
set(USE_IMX477_SQUARE_CAMERA_MIPI 0)
set(USE_HVGS_GRAY_USB_CAMERA 0) # GLOBAL SHUTTER USB CAMERA
set(USE_SHARED_MEMORY 0)
set(USE_HIKVISION 1)

# Использование версии Yolo v3, v4 или trt: (if CORE_TYPE = 10 )
set(USE_YOLO_VERSION trt)

set(OpenCV_DIR $ENV{HOME}/opencv/install_4_7_0_contrib_cuda)

set(USE_CUDA_RESIZE_DEVICE_IMX219 0) # использование resize через cv::cuda на уровне device
set(SYSTEM_ENDIANNESS LITTLE) # системный порядок байтов LITTLE / BIG (зачастую LITTLE).

##################################################################################################

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/run) # директория сборки проекта

set(LIST_VALID_COLOR_CHANNEL_MODES 8UC1 8UC2 8UC3 8UC4)

if(NOT ${USE_COLOR_CHANNEL_MODE} IN_LIST LIST_VALID_COLOR_CHANNEL_MODES)
    message("Note: valid COLOR_CHANNEL_MODE list: " "${LIST_VALID_COLOR_CHANNEL_MODES}")
    message(FATAL_ERROR "Error: not recognize \"COLOR_CHANNEL_MODE\" mode = \"${USE_COLOR_CHANNEL_MODE}\"")
else()
    message(STATUS "USE_COLOR_CHANNEL_MODE = ${USE_COLOR_CHANNEL_MODE}")
    add_definitions(-DCCM_${USE_COLOR_CHANNEL_MODE})
endif()

if(${USE_GUI} EQUAL 1)
    add_definitions(-DGUI_OK)
    message(STATUS "--------------------------- USE_GUI=1")
else()
    set(SHOW_PSTFX )
    message(STATUS "--------------------------- USE_GUI=0")
endif()

if(${USE_CORR_TYPE} EQUAL 10)
    add_definitions(-DTKDNN)
    set(YOLO_LIB_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/../../darknet4)
    set(TKDNN_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/../../tkDNN)

    message(STATUS "--------------------------- USE TKDNN")
    message(STATUS "--------------------------- USE_YOLO_${USE_YOLO_VERSION}")

    if(${USE_YOLO_VERSION} STREQUAL v3 OR ${USE_YOLO_VERSION} STREQUAL v4)
        set(YOLO_LIB -ldarknet_${GPU_PREFIX}_${USE_YOLO_VERSION})
        set(COPTER_LIB -l_copter_scan_y${USE_YOLO_VERSION}_${WORK_IN})
    elseif(${USE_YOLO_VERSION} STREQUAL trt)
        set(YOLO_LIB -ltkdnn_yolo)
        set(COPTER_LIB -l_copter_scan_trt_${WORK_IN})
        add_definitions(-DYOLO_${USE_YOLO_VERSION})
        message(STATUS "--------------------------- USE_YOLO_${USE_YOLO_VERSION}")
    endif()
    link_directories(${TKDNN_DIRECTORY})
    link_directories(${YOLO_LIB_DIRECTORY})

endif()



if(${USE_DBG} EQUAL 1)
    add_definitions(-DUSE_DBG)
endif()

if(${USE_ETH_MD} EQUAL 1)
    add_definitions(-DUSE_ETH_MD)
endif()

if(${USE_TCP_SETUP} EQUAL 1)
    add_definitions(-DUSE_TCP_SETUP)
endif()

set(CMAKE_MAKE_PROGRAM "make -j${nproc}")
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})
link_directories(${CMAKE_CURRENT_LIST_DIR})

find_package(OpenCV REQUIRED PATHS ${OpenCV_DIR} NO_DEFAULT_PATH)
message(OpenCV_INCLUDE_DIRS=${OpenCV_INCLUDE_DIRS})
include_directories(${OpenCV_INCLUDE_DIRS})

link_directories(${CMAKE_CURRENT_LIST_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/lib_modules)


add_definitions(-DAP_TEMETRY_INTERFACE_PATH="${CMAKE_CURRENT_LIST_DIR}/modules/chain_drone_telemetry_ap/chain_drone_telemetry_ap.hpp")
add_definitions(-DTRACKER_METADATA_INTERFACE_PATH="${CMAKE_CURRENT_LIST_DIR}/modules/trackmeta2ap/trackmeta2ap.hpp")
add_definitions(-DTRACKER_METADATA_POS_INTERFACE_PATH="${CMAKE_CURRENT_LIST_DIR}/modules/trackmeta2ap/trackmeta2ap_pos.hpp")

include_directories(tools/)

    file(GLOB TracShatsFiles "${CMAKE_CURRENT_LIST_DIR}/tracshats/*")

add_executable(chain_drone_server
    chain_drone_server.ini
    main.cpp
    application.cpp
    show_res.cpp
    application.hpp
    application_struct.hpp

    ##############     Trackers     ###################################################
    ${TracShatsFiles}
    ##############      Tools       ####################################################
    tools/INIReader.h
    tools/ExtendINIReader.hpp
    tools/watchdog.h
    tools/colors.h
    
    #    tools/recorder/recorder.hpp
    #    tools/recorder/recorder.cpp
    
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
    devices/icommandhandler.h
    )

if(${USE_ETH_CONTROLLER} EQUAL 1)

    add_library(track_meta_pos_sender SHARED
        modules/trackmeta2ap/trackmeta2ap_pos.hpp
        modules/track_meta_pos_sender/track_meta_pos_sender.hpp
        modules/track_meta_pos_sender/track_meta_pos_sender.cpp
        modules/track_meta_pos_sender/track_meta_pos_sender_factory.hpp
        modules/track_meta_pos_sender/track_meta_pos_sender_factory.cpp
        )
    target_link_libraries(track_meta_pos_sender eth_controller_toolbox_lib)
    target_link_libraries(chain_drone_server track_meta_pos_sender)

    add_definitions(-DUSE_ETH_CONTROLLER)

    add_library(path_processing SHARED
        tools/path_processing/path_processing.hpp
        tools/path_processing/path_processing.cpp
        )

    add_library(string_toolbox SHARED
        tools/string_toolbox/string_processing.cpp
        tools/string_toolbox/string_processing.hpp
        )

    add_library(sys_time_toolbox SHARED
        tools/sys_time_toolbox/sys_time_extract.hpp
        tools/sys_time_toolbox/sys_time_extract.cpp
        )

    add_library(ap_tele_keeper SHARED
        modules/eth_chain_drone_ap_telemetry_keeper/eth_chain_drone_ap_telemetry_keeper.hpp
        modules/eth_chain_drone_ap_telemetry_keeper/eth_chain_drone_ap_telemetry_keeper.cpp
        modules/eth_chain_drone_ap_telemetry_keeper/eth_chain_drone_ap_telemetry_keeper_factory.hpp
        modules/eth_chain_drone_ap_telemetry_keeper/eth_chain_drone_ap_telemetry_keeper_factory.cpp
        modules/chain_drone_telemetry_ap/chain_drone_telemetry_ap.hpp

        tools/INIReader.h
        tools/ExtendINIReader.hpp
        )
    target_link_libraries(ap_tele_keeper eth_controller_toolbox_lib)
    target_link_libraries(chain_drone_server ap_tele_keeper #[[telemetry_multiplexor]])
endif()


add_library(fenix2cmd_keeper SHARED
    modules/fenix2cmd/fenix2cmd_struct.hpp
    modules/fenix2cmd_keeper/fenix2cmd_keeper.hpp
    modules/fenix2cmd_keeper/fenix2cmd_keeper.cpp
    modules/fenix2cmd_keeper/fenix2cmd_keeper_factory.hpp
    modules/fenix2cmd_keeper/fenix2cmd_keeper_factory.cpp
    )
target_link_libraries(fenix2cmd_keeper eth_controller_toolbox_lib)
target_link_libraries(chain_drone_server fenix2cmd_keeper)

add_subdirectory(modules/eth_controller_toolbox/)
include_directories(modules/eth_controller_toolbox/)
target_link_libraries(chain_drone_server eth_controller_toolbox_lib)

if (${USE_TCP_SETUP} EQUAL 1)
    add_definitions(-DUSE_TCP_SETUP)
    add_library(tcp_server_setup_info SHARED
        modules/tcp_server_setup_info/setup_info_struct.hpp
        modules/tcp_server_setup_info/tcp_server_setup_info.cpp
        modules/tcp_server_setup_info/tcp_server_setup_info.hpp
        modules/tcp_server_setup_info/tcp_server_setup_info_factory.cpp
        modules/tcp_server_setup_info/tcp_server_setup_info_factory.hpp
        )
    target_link_libraries(tcp_server_setup_info eth_controller_toolbox_lib)
    target_link_libraries(chain_drone_server tcp_server_setup_info)
endif()


if(${USE_LOGGER} EQUAL 1)
    add_definitions(-DUSE_LOGGER)
    target_sources(chain_drone_server PRIVATE
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
    target_sources(chain_drone_server PRIVATE
        devices/FolderReader/folderreader.h
        devices/FolderReader/folderreader.cpp
        )
endif()

if(${USE_VIDEO_READER} EQUAL 1)
    add_definitions(-DUSE_VIDEO_READER)
    target_sources(chain_drone_server PRIVATE
        devices/VideoReader/videoreader.h
        devices/VideoReader/videoreader.cpp
        )
endif()

if(${USE_WEB_CAMERA} EQUAL 1)
    add_definitions(-DUSE_WEB_CAMERA)
    target_sources(chain_drone_server PRIVATE
        devices/WebCamera/webcamera.hpp
        devices/WebCamera/webcamera.cpp
        )
endif()

if(${USE_RASPBERRY_HQ_CAMERA} EQUAL 1)
    add_definitions(-DUSE_RASPBERRY_HQ_CAMERA)
    target_sources(chain_drone_server PRIVATE
        devices/RaspberryHQCamera/raspberryhqcamera.cpp
        devices/RaspberryHQCamera/raspberryhqcamera.hpp
        devices/RaspberryHQCamera/factory.cpp
        devices/RaspberryHQCamera/factory.hpp
        devices/RaspberryHQCamera/settings.hpp
        )
    target_link_libraries(chain_drone_server ${GST_LIBRARIES} gstapp-1.0)
    target_include_directories(chain_drone_server PRIVATE ${GST_INCLUDE_DIRS})
endif()

if(${USE_IMX219_CAMERA_MIPI} EQUAL 1)
    add_definitions(-DUSE_IMX219_CAMERA_MIPI)
    target_sources(chain_drone_server PRIVATE
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
    target_sources(chain_drone_server PRIVATE
        devices/imx477squareCameraMIPI/imx477_square_camera_mipi_factory.hpp
        devices/imx477squareCameraMIPI/imx477_square_camera_mipi_factory.cpp
        devices/imx477squareCameraMIPI/imx477_square_camera_mipi.hpp
        devices/imx477squareCameraMIPI/imx477_square_camera_mipi.cpp
        devices/imx477squareCameraMIPI/imx477_square_camera_mipi_settings.hpp
    )
endif()


if(${USE_HVGS_GRAY_USB_CAMERA} EQUAL 1)
    add_definitions(-DUSE_HVGS_GRAY_USB_CAMERA)
    target_sources(chain_drone_server PRIVATE
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
    target_link_libraries(chain_drone_server lib_hvgs_camera)
endif()

if(${USE_HIKVISION} EQUAL 1)
    add_definitions(-DUSE_HIKVISION)
    include_directories(tools/)
    include_directories(tools/toolbox_common_utils/)
    target_sources(chain_drone_server PRIVATE
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
    target_link_libraries(chain_drone_server ${GST_LIBRARIES} ${GST_LIBRARIES} gstapp-1.0)
    target_include_directories(chain_drone_server PRIVATE ${GST_INCLUDE_DIRS})

endif()


if(${USE_RECORDER} EQUAL 1)
    add_definitions(-DUSE_RECORDER)
    add_library(recorder SHARED
        tools/recorder_HVGS/recorder_srst.hpp
        tools/recorder_HVGS/recorder_srst.cpp
        tools/recorder_HVGS/recorder_base.hpp
        tools/ts_pipe_frame_buf/async_frame_bank.cpp
        tools/ts_pipe_frame_buf/async_frame_bank.hpp
        tools/ts_pipe_frame_buf/ts_pipe_frame_buf.cpp
        tools/ts_pipe_frame_buf/ts_pipe_frame_buf.hpp
        )

    add_library(test_disk_monitor
        tools/disk_monitor/disk_monitor.hpp
        tools/disk_monitor/disk_monitor.cpp
        tools/disk_monitor/live_disk_monitor.hpp
        tools/disk_monitor/live_disk_monitor.cpp
        )

target_link_libraries(chain_drone_server test_disk_monitor recorder path_processing)
endif()

if(${USE_GUI} EQUAL 0)
    set(GUI_RUN_PSTFX "notgui")
elseif(${USE_GUI} EQUAL 1)
    set(GUI_RUN_PSTFX "gui")
else()
    message(FATAL_ERROR "Error: incorrect \"USE_GUI\" parameter = \"#{USE_GUI}\"")
    endif()

    #                     gui/notgui    8UC1/8UC2/8UC3/16FC1 etc..
    set(run_name run_chain_drone_server_${GUI_RUN_PSTFX}_${USE_COLOR_CHANNEL_MODE}_${USE_CORR_TYPE})

    if(${USE_CORR_TYPE} EQUAL 0)
        add_definitions(-DUSE_CUDA)
    endif()
        target_link_libraries(chain_drone_server ${OpenCV_LIBS} -lrt -l_trac_tmml_${USE_CORR_TYPE}_CUDA -lpthread)
    set_target_properties(chain_drone_server PROPERTIES OUTPUT_NAME ${run_name})
