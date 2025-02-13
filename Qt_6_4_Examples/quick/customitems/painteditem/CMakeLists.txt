cmake_minimum_required(VERSION 3.16)
project(painteditem LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/quick/customitems/painteditem")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick)

add_subdirectory(TextBalloon)

qt_add_executable(painteditemexample WIN32 MACOSX_BUNDLE main.cpp)

qt_add_qml_module(painteditemexample
    URI painteditem
    VERSION 1.0
    QML_FILES
        "textballoons.qml"
)

target_link_libraries(painteditemexample PRIVATE
    Qt::Core
    Qt::Gui
    Qt::Qml
    Qt::Quick
)

add_dependencies(painteditemexample qmltextballoon)

install(TARGETS painteditemexample
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)

include(../../shared/QtBundleQmlModuleForMacOS.cmake)

set(app_target "painteditemexample")
set(qml_plugin_target "qmltextballoon")
set(qml_module_uri "TextBalloon")
add_qml_module_to_macos_app_bundle(
    "${app_target}" "${qml_plugin_target}" "${qml_module_uri}")
