cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 17)

project(chain_drone_client)

set(OpenCV_DIR $ENV{HOME}/opencv/install_4_7_0_contrib_cuda)
find_package(OpenCV REQUIRED PATHS ${OpenCV_DIR} NO_DEFAULT_PATH)
add_definitions(-DCCM_8UC1)
set(GST_API_TYPE 1) # 0 - CV_API, 1 - C_API_H264, 2 - C_API_H265, 3 - C_API_MPEG, 4 - C_API_RAW;
set(USE_TCP_SETUP 0) # 1 - принимаем тип трекера (и другие команды по желанию) при установке соединения с клиентом
set(USE_SPEAKER 1)
set(TKDNN 1) # использование нейросети для поиска шаблона

######################################################################

set(threads_num ${nproc}) # Число потоков компиляции.
set(CMAKE_MAKE_PROGRAM "make -j${threads_num}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/run) # директория сборки проекта
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/lib_modules)

add_subdirectory(modules/eth_controller_toolbox/)
include_directories(modules/eth_controller_toolbox/)
#link_directories(modules/eth_controller_toolbox/)


include_directories(
    ${OpenCV_INCLUDE_DIRS}
    modules/eth_controller_toolbox/
    tools/
    modules/meta_keeper/
    modules/)

add_executable(chain_drone_client
    main.cpp
    chain_drone_client.hpp
    chain_drone_client.cpp
    tools/INIReader.h
    tools/ExtendINIReader.hpp
    tools/watchdog.h
    tools/colors.h
    chain_drone_client.ini
    )

if(${TKDNN} EQUAL 1)
    add_definitions(-DTKDNN)
endif()

if (${USE_TCP_SETUP} EQUAL 1)
    add_definitions(-DUSE_TCP_SETUP)
    add_library(tcp_client_setup_info SHARED
        modules/tcp_client_setup_info/setup_info_struct.hpp
        modules/tcp_client_setup_info/tcp_client_setup_info.cpp
        modules/tcp_client_setup_info/tcp_client_setup_info.hpp
        modules/tcp_client_setup_info/tcp_client_setup_info_factory.cpp
        modules/tcp_client_setup_info/tcp_client_setup_info_factory.hpp
        )
    target_link_libraries(tcp_client_setup_info eth_controller_toolbox_lib)
    target_link_libraries(chain_drone_client tcp_client_setup_info)
endif()

if (${USE_SPEAKER} EQUAL 1)
    add_definitions(-DUSE_SPEAKER)
endif()

if(${GST_API_TYPE} EQUAL 0)
    add_definitions(-DGST_CVAPI)
    add_library(fenix2meta_keeper SHARED
        modules/meta_struct/meta_struct.hpp # структура телеметрии клиента феникса 2
        modules/meta_keeper/fenix2meta_keeper.hpp
        modules/meta_keeper/fenix2meta_keeper.cpp
        modules/meta_keeper/fenix2meta_keeper_factory.hpp
        modules/meta_keeper/fenix2meta_keeper_factory.cpp
        tools/sys_time_toolbox/sys_time_extract.cpp
        tools/sys_time_toolbox/sys_time_extract.hpp
        )
    target_include_directories(fenix2meta_keeper PRIVATE $ENV{HOME}/QtProg/eth_ap_test_platform/modules/)
    target_link_libraries(fenix2meta_keeper eth_controller_toolbox_lib)
    target_link_libraries(chain_drone_client fenix2meta_keeper)
elseif (${GST_API_TYPE} EQUAL 1)
    add_definitions(-DGST_CAPI_H264)
elseif (${GST_API_TYPE} EQUAL 2)
    add_definitions(-DGST_CAPI_H265)
elseif (${GST_API_TYPE} EQUAL 3)
    add_definitions(-DGST_CAPI_MJPEG)
elseif (${GST_API_TYPE} EQUAL 4)
    add_definitions(-DGST_CAPI_RAW)
endif()

set(SYSTEM_ENDIANNESS LITTLE) # системный порядок байтов LITTLE / BIG (зачастую LITTLE).

add_library(cmd_sender SHARED
    modules/cmd_struct/cmd_struct.hpp
    modules/cmd_sender/fenix2cmd_sender.hpp
    modules/cmd_sender/fenix2cmd_sender.cpp
    modules/cmd_sender/fenix2cmd_sender_factory.hpp
    modules/cmd_sender/fenix2cmd_sender_factory.cpp
    )
target_link_libraries(cmd_sender eth_controller_toolbox_lib)


target_link_libraries(chain_drone_client
    ${OpenCV_LIBS}
    -lrt
    -lpthread
    eth_controller_toolbox_lib
    cmd_sender
    -lX11
    )
