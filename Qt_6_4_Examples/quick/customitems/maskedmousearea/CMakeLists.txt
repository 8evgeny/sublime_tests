cmake_minimum_required(VERSION 3.16)
project(maskedmousearea LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/quick/customitems/maskedmousearea")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick)

qt_add_executable(maskedmousearea
    main.cpp
    maskedmousearea.cpp maskedmousearea.h
)

set_target_properties(maskedmousearea PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(maskedmousearea PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Qml
    Qt::Quick
)

qt_add_qml_module(maskedmousearea
    URI Example
    VERSION 1.0
    QML_FILES
        maskedmousearea.qml
    RESOURCES
        images/cloud_1.png
        images/cloud_2.png
        images/moon.png
    RESOURCE_PREFIX /customitems/maskedmousearea
    NO_RESOURCE_TARGET_PATH
)

install(TARGETS maskedmousearea
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
