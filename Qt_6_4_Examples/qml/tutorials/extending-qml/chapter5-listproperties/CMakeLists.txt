cmake_minimum_required(VERSION 3.16)
project(chapter5-listproperties LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/qml/tutorials/extending-qml/chapter5-listproperties")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick)

qt_add_executable(chapter5-listproperties
    main.cpp
    piechart.cpp piechart.h
    pieslice.cpp pieslice.h
)

set_target_properties(chapter5-listproperties PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(chapter5-listproperties PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Qml
    Qt::Quick
)

qt_add_qml_module(chapter5-listproperties
    URI Charts
    VERSION 1.0
    QML_FILES app.qml
    NO_RESOURCE_TARGET_PATH
)

install(TARGETS chapter5-listproperties
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
