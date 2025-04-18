cmake_minimum_required(VERSION 3.16)
project(chapter6-plugins LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/qml/tutorials/extending-qml/chapter6-plugins")

find_package(Qt6 REQUIRED COMPONENTS Qml Quick)

qt_add_executable(chapter6-plugins
    main.cpp
)

set_target_properties(chapter6-plugins PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(chapter6-plugins PRIVATE
    Qt::Qml
    Qt::Quick
)

qt_add_qml_module(chapter6-plugins
    URI ChartsApp
    VERSION 1.0
    QML_FILES app.qml
    NO_RESOURCE_TARGET_PATH
)

install(TARGETS chapter6-plugins
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)

add_subdirectory(Charts)
