cmake_minimum_required(VERSION 3.16)
project(chapter1-basics LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/qml/tutorials/extending-qml/chapter1-basics")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick)

qt_add_executable(chapter1-basics
    main.cpp
    piechart.cpp piechart.h
)

set_target_properties(chapter1-basics PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(chapter1-basics PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Qml
    Qt::Quick
)
#![0]
qt_add_qml_module(chapter1-basics
    URI Charts
    VERSION 1.0
    QML_FILES app.qml
    NO_RESOURCE_TARGET_PATH
)
#![0]
install(TARGETS chapter1-basics
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
