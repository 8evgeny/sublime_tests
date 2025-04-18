cmake_minimum_required(VERSION 3.16)
project(blockingfortuneclient LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/network/blockingfortuneclient")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Network Widgets)

qt_add_executable(blockingfortuneclient
    blockingclient.cpp blockingclient.h
    fortunethread.cpp fortunethread.h
    main.cpp
)

set_target_properties(blockingfortuneclient PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(blockingfortuneclient PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Network
    Qt::Widgets
)

install(TARGETS blockingfortuneclient
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
