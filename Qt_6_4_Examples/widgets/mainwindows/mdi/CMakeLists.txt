cmake_minimum_required(VERSION 3.16)
project(mdi LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/widgets/mainwindows/mdi")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

qt_add_executable(mdi
    main.cpp
    mainwindow.cpp mainwindow.h
    mdichild.cpp mdichild.h
)

set_target_properties(mdi PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(mdi PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Widgets
)

# Resources:
set(mdi_resource_files
    "images/copy.png"
    "images/cut.png"
    "images/new.png"
    "images/open.png"
    "images/paste.png"
    "images/save.png"
)

qt_add_resources(mdi "mdi"
    PREFIX
        "/"
    FILES
        ${mdi_resource_files}
)

install(TARGETS mdi
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
