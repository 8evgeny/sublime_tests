cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 17)

project(trac_from_lib_tmml)
message(STATUS "")
message(STATUS "-------------------------------- CMAKE BEGINING for project trac_from_lib_tmml")


# Использование GPU:
set(USE_GPU 1) # (0 - CPU, 1 - CUDA, 2 - OPENCL)


# Тип корреляции при template matching для USE_CORR_TYPE:
# CORR_TYPE = 2 : SQDIFF_NORMED (Прямая корреляция)
# CORR_TYPE = 6 : CCOEFF_NORMED  (Кросскорреляция модифицированная)
# CORR_TYPE = 8 ; COMBINED (объединение прямой и модифицированной кросскорреляции)
# CORR_TYPE = 10 : TKDNN
set(USE_CORR_TYPE 10)

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
# Use Devices:
set(USE_FOLDER_READER 1) # 0
set(USE_VIDEO_READER 0) # 1
set(USE_WEB_CAMERA 0) # 2
set(USE_COLIBRI_TV 0) # 3
set(USE_RASPBERRY_HQ_CAMERA 0) # 4
set(USE_IMX477_SQUARE_CAMERA_MIPI 0) # 5
set(USE_IMX219_CAMERA_MIPI 0) # 6
set(USE_HIKVISION 0) # 7
set(USE_SHARED_MEMORY 0) # 8
set(USE_HVGS_GRAY_USB_CAMERA 0) # 9
set(USE_CORSAIR_400_RAW 0) # 10 (Шар ОЭЦН400, сырой UDP видеопоток напрямую)
set(USE_ETHERNET_CONNECTION 0)
set(USE_PCAP 0)

set(OpenCV_DIR $ENV{HOME}/opencv/install_4_7_0_contrib_cuda)

set(USE_CUDA_RESIZE_DEVICE_IMX219 0) # использование resize через cv::cuda на уровне device
set(SYSTEM_ENDIANNESS LITTLE) # системный порядок байтов LITTLE / BIG (зачастую LITTLE).

# Использование версии Yolo v3, v4 или trt:
set(USE_YOLO_VERSION trt)
set(GPU_LIB_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/../../darknet4)
set(TKDNN_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/../../tkDNN)

if(${USE_CORSAIR_400_RAW} EQUAL 1)
    set(DBG_VIDEO_SENDER 0) # включение отправки видео и командного обмена с эмулятором шара (QtProg/poes400/corsair_terminal_emulator)
    # Используем программу в паре с терминалкой 400-го, раздел ini-файла [vtrack_data_sender], подключаем библиотеку vtrack_data_sender
    set(USE_DBG_SEND_VTRACK 0) # дополнителоное логирование отладочной информации в процессе отправки рамок целей
    set(USE_VERTELKA_CMD 1) # использование удалённого переключения трека/ткднн
endif() #     if(${USE_CORSAIR_400_RAW} EQUAL 1)
#################################################################################################

if(${USE_GPU} EQUAL 0)
    set(GPU_PREFIX cpu)
    message(STATUS "--------------------------- USE_CPU")
endif() # END if(${USE_GPU} EQUAL 0)

if(${USE_GPU} EQUAL 1)
    if(${USE_CORR_TYPE} EQUAL 10)
        set(GPU_PREFIX gpu)
        if(${USE_YOLO_VERSION} STREQUAL v3 OR ${USE_YOLO_VERSION} STREQUAL v4)
            set(GPU_LIB -ldarknet_${GPU_PREFIX}_${USE_YOLO_VERSION})
        elseif(${USE_YOLO_VERSION} STREQUAL trt)
            set(GPU_LIB -ltkdnn_yolo)
        endif() # END elseif(${USE_YOLO_VERSION} STREQUAL trt)

        link_directories(${TKDNN_DIRECTORY})
        link_directories(${GPU_LIB_DIRECTORY})
        add_definitions(-DYOLO_${USE_YOLO_VERSION})
        message(STATUS "--------------------------- USE_YOLO_${USE_YOLO_VERSION}")
    endif() # END if(${USE_CORR_TYPE} EQUAL 10)
endif() # END if(${USE_GPU} EQUAL 1)

if(${USE_GPU} EQUAL 2)
    include_directories($CMAKE_SOURCE_DIR})
    find_package(OpenCL REQUIRED)
    include_directories (${OpenCL_INCLUDE_DIRS})
    set(GPU_LIB ${OpenCL_LIBRARY})
endif() # END if(${USE_GPU} EQUAL 2)

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

if(${USE_GPU} EQUAL 0)
    set(trac_lib_name -l_trac_tmml_${USE_CORR_TYPE}_CPU) # Название подключаемой библиотеки CPU
    add_definitions(-DUSE_CPU)
    message(STATUS "--------------------------- USE_CORR_TYPE=${USE_CORR_TYPE}")
    message(STATUS "--------------------------- USE_CPU")
endif() # END if(${USE_GPU} EQUAL 0)

if(${USE_GPU} EQUAL 1)
    if(NOT ${USE_CORR_TYPE} EQUAL 10)
        set(trac_lib_name -l_trac_tmml_${USE_CORR_TYPE}_CUDA) # Название подключаемой библиотеки CUDA
    endif()
    if(${USE_CORR_TYPE} EQUAL 10)
        set(trac_lib_name -l_trac_tmml_TKDNN) # Название подключаемой библиотеки CUDA
        add_definitions(-DTKDNN)
        message(STATUS "--------------------------- USE_CORR_TYPE=${USE_CORR_TYPE}")
        message(STATUS "--------------------------- USE_TKDNN")
    endif()
    add_definitions(-DUSE_CUDA)
    message(STATUS "--------------------------- USE_CORR_TYPE=${USE_CORR_TYPE}")
    message(STATUS "--------------------------- USE_CUDA")
endif() # END if(${USE_GPU} EQUAL 1)

if(${USE_GPU} EQUAL 2)
    set(trac_lib_name -l_trac_tmml_${USE_CORR_TYPE}_CL) # Название подключаемой библиотеки CUDA
    add_definitions(-DUSE_CL)
    message(STATUS "--------------------------- USE_CORR_TYPE=${USE_CORR_TYPE}")
    message(STATUS "--------------------------- USE_CL")
endif() # END if(${USE_GPU} EQUAL 2)

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

file(GLOB TracShatsFiles "${CMAKE_CURRENT_LIST_DIR}/tracshats/*")

add_executable(trac_from_lib_tmml
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
    target_sources(trac_from_lib_tmml PRIVATE
        logger/logger.cpp
        logger/logger.hpp
        logger/factory.cpp
        logger/factory.h
        logger/settings.hpp)
endif() # END if(${USE_LOGGER} EQUAL 1)

########################### BEGIN DEVICES:

if(${USE_FOLDER_READER} EQUAL 1) # 0
    add_definitions(-DUSE_FOLDER_READER)
    target_sources(trac_from_lib_tmml PRIVATE
        devices/FolderReader/folderreader.h
        devices/FolderReader/folderreader.cpp
        )
endif() # END if(${USE_FOLDER_READER} EQUAL 1)

if(${USE_VIDEO_READER} EQUAL 1) # 1
    add_definitions(-DUSE_VIDEO_READER)
    target_sources(trac_from_lib_tmml PRIVATE
        devices/VideoReader/videoreader.h
        devices/VideoReader/videoreader.cpp
        )
endif() # END if(${USE_VIDEO_READER} EQUAL 1)

if(${USE_WEB_CAMERA} EQUAL 1) # 2
    add_definitions(-DUSE_WEB_CAMERA)
    target_sources(trac_from_lib_tmml PRIVATE
        devices/WebCamera/webcamera.hpp
        devices/WebCamera/webcamera.cpp
        )
endif() # END if(${USE_WEB_CAMERA} EQUAL 1)

if(${USE_COLIBRI_TV} EQUAL 1) # 3
    add_definitions(-DUSE_COLIBRI_TV)
    set(USE_ETHERNET_CONNECTION 1)
    target_sources(trac_from_lib_tmml PRIVATE
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
    target_sources(trac_from_lib_tmml PRIVATE
        devices/RaspberryHQCamera/raspberryhqcamera.cpp
        devices/RaspberryHQCamera/raspberryhqcamera.hpp
        devices/RaspberryHQCamera/factory.cpp
        devices/RaspberryHQCamera/factory.hpp
        devices/RaspberryHQCamera/settings.hpp
        )
    target_link_libraries(trac_from_lib_tmml ${GST_LIBRARIES} gstapp-1.0)
    target_include_directories(trac_from_lib_tmml PRIVATE ${GST_INCLUDE_DIRS})
endif() # END if(${USE_RASPBERRY_HQ_CAMERA} EQUAL 1)

if(${USE_IMX477_SQUARE_CAMERA_MIPI} EQUAL 1) # 5
    add_definitions(-DUSE_IMX477_SQUARE_CAMERA_MIPI)
    target_sources(trac_from_lib_tmml PRIVATE
        devices/imx477squareCameraMIPI/imx477_square_camera_mipi_factory.hpp
        devices/imx477squareCameraMIPI/imx477_square_camera_mipi_factory.cpp
        devices/imx477squareCameraMIPI/imx477_square_camera_mipi.hpp
        devices/imx477squareCameraMIPI/imx477_square_camera_mipi.cpp
        devices/imx477squareCameraMIPI/imx477_square_camera_mipi_settings.hpp
        )
endif() # END if(${USE_IMX477_SQUARE_CAMERA_MIPI} EQUAL 1)

if(${USE_IMX219_CAMERA_MIPI} EQUAL 1) # 6
    add_definitions(-DUSE_IMX219_CAMERA_MIPI)
    target_sources(trac_from_lib_tmml PRIVATE
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

if(${USE_HIKVISION} EQUAL 1) # 7
    add_definitions(-DUSE_HIKVISION)
    include_directories(tools/)
    include_directories(tools/toolbox_common_utils/)
    target_sources(trac_from_lib_tmml PRIVATE
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
    target_link_libraries(trac_from_lib_tmml ${GST_LIBRARIES} ${GST_LIBRARIES} gstapp-1.0)
    target_include_directories(trac_from_lib_tmml PRIVATE ${GST_INCLUDE_DIRS})
endif() # END if(${USE_HIKVISION} EQUAL 1)

if(${USE_SHARED_MEMORY} EQUAL 1) # 8
    add_definitions(-DUSE_SHARED_MEMORY)
    target_sources(trac_from_lib_tmml PRIVATE
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
    target_link_libraries(trac_from_lib_tmml -lrt)
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
    target_sources(trac_from_lib_tmml PRIVATE
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
        ) # END target_sources(trac_from_lib_tmml PRIVATE
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
    target_sources(trac_from_lib_tmml PRIVATE
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
        target_sources(trac_from_lib_tmml PRIVATE
            eth/socket/pcapclient.cpp
            eth/socket/pcapsocket.h
            eth/socket/pcapclient.h
            eth/socket/pcapserver.cpp
            eth/socket/pcapserver.h
            eth/socket/pcapsocket.cpp
            )
        target_link_libraries(trac_from_lib_tmml -lpcap)
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
    target_link_libraries(trac_from_lib_tmml vtrack_data_sender)

    add_subdirectory(modules/eth_controller_toolbox)
    include_directories(modules/eth_controller_toolbox/)

    add_library(cmd400_keeper SHARED
        modules/cmd400/cmd400_struct.hpp
        modules/cmd400/cmd400_keeper.hpp
        modules/cmd400/cmd400_keeper.cpp
        modules/cmd400/cmd400_keeper_factory.hpp
        modules/cmd400/cmd400_keeper_factory.cpp
        )
    target_link_libraries(trac_from_lib_tmml vtrack_data_sender cmd400_keeper eth_controller_toolbox_lib)


endif() # END if(${USE_CORSAIR_400_RAW} EQUAL 1)


add_executable(vertelka vertelka.cpp)

if(${USE_CORSAIR_400_RAW} EQUAL 1)
    if(${USE_VERTELKA_CMD} EQUAL 1)
        add_definitions(-DUSE_VERTELKA_CMD)
        add_library(vertelka_cmd SHARED
            modules/cmd_vertelka/cmd_vertelka_keeper.hpp
            modules/cmd_vertelka/cmd_vertelka_keeper.cpp
            modules/cmd_vertelka/cmd_vertelka_keeper_factory.hpp
            modules/cmd_vertelka/cmd_vertelka_keeper_factory.cpp
            modules/cmd_vertelka/cmd_vertelka_struct.hpp
            )
        target_link_libraries(vertelka vertelka_cmd eth_controller_toolbox_lib)
    endif() # END if(${USE_VERTELKA_CMD} EQUAL 1)
endif() # END if(${USE_CORSAIR_400_RAW} EQUAL 1)

target_link_libraries(vertelka ${OpenCV_LIBS})
if(${USE_GUI} EQUAL 0)
    set(GUI_RUN_PSTFX "notgui")
elseif(${USE_GUI} EQUAL 1)
    set(GUI_RUN_PSTFX "gui")
else()
    message(FATAL_ERROR "Error: incorrect \"USE_GUI\" parameter = \"#{USE_GUI}\"")
    endif() # END if(NOT ${USE_GUI} EQUAL 0)

    if(${USE_GPU} EQUAL 0)
        set(run_name run_${GUI_RUN_PSTFX}_${USE_COLOR_CHANNEL_MODE}_${USE_CORR_TYPE}_CPU)
    endif() # END if(${USE_GPU} EQUAL 0)

    if(${USE_GPU} EQUAL 1)
        if(${USE_CORR_TYPE} EQUAL 10)
            set(run_name run_${GUI_RUN_PSTFX}_${USE_COLOR_CHANNEL_MODE}_TKDNN)
        endif() # END if(${USE_CORR_TYPE} EQUAL 10)
        if(NOT ${USE_CORR_TYPE} EQUAL 10)
            set(run_name run_${GUI_RUN_PSTFX}_${USE_COLOR_CHANNEL_MODE}_${USE_CORR_TYPE}_CUDA)
        endif() # END if(NOT ${USE_CORR_TYPE} EQUAL 10)
    endif() # END if(${USE_GPU} EQUAL 1)

    if(${USE_GPU} EQUAL 2)
        set(run_name run_${GUI_RUN_PSTFX}_${USE_COLOR_CHANNEL_MODE}_${USE_CORR_TYPE}_CL)
    endif() # END if(${USE_GPU} EQUAL 2)

    target_link_libraries(trac_from_lib_tmml ${OpenCV_LIBS} ${GPU_LIB} ${trac_lib_name} -lrt -lpthread)
    target_link_libraries(trac_from_lib_tmml ${OpenCV_LIBS} ${GPU_LIB} ${trac_lib_name} -lrt -lpthread)
    set_target_properties(trac_from_lib_tmml PROPERTIES OUTPUT_NAME ${run_name})
