cmake_minimum_required(VERSION 3.16)
project(secureudpclient LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/network/secureudpclient")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Network Widgets)

qt_add_executable(secureudpclient
    addressdialog.cpp addressdialog.h addressdialog.ui
    association.cpp association.h
    main.cpp
    mainwindow.cpp mainwindow.h mainwindow.ui
)

set_target_properties(secureudpclient PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(secureudpclient PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Network
    Qt::Widgets
)

install(TARGETS secureudpclient
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
