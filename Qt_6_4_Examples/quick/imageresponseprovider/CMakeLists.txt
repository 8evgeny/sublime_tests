cmake_minimum_required(VERSION 3.16)
project(qmlimageresponseproviderplugin LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/quick/imageresponseprovider/ImageResponseProviderCore")
set(QT_QML_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/examples/quick/imageresponseprovider)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick)

qt6_add_qml_module(qmlimageresponseproviderplugin
    VERSION 1.0
    URI "ImageResponseProviderCore"
    PLUGIN_TARGET qmlimageresponseproviderplugin
    NO_PLUGIN_OPTIONAL
    NO_GENERATE_PLUGIN_SOURCE
    CLASS_NAME ImageProviderExtensionPlugin
)

target_sources(qmlimageresponseproviderplugin PRIVATE
    imageresponseprovider.cpp
)

set_target_properties(qmlimageresponseproviderplugin PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(qmlimageresponseproviderplugin PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Qml
    Qt::Quick
)

install(TARGETS qmlimageresponseproviderplugin
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
