cmake_minimum_required(VERSION 3.16)
project(chapter4-customPropertyTypes LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/qml/tutorials/extending-qml/chapter4-customPropertyTypes")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick)
#![0]
qt_add_executable(chapter4-customPropertyTypes
    main.cpp
    piechart.cpp piechart.h
    pieslice.cpp pieslice.h
)
#![0]
set_target_properties(chapter4-customPropertyTypes PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(chapter4-customPropertyTypes PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Qml
    Qt::Quick
)
#![1]
qt_add_qml_module(chapter4-customPropertyTypes
    URI Charts
    VERSION 1.0
    QML_FILES app.qml
    NO_RESOURCE_TARGET_PATH
)
#![1]
install(TARGETS chapter4-customPropertyTypes
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
