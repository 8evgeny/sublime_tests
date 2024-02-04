cmake_minimum_required(VERSION 3.16)
project(quickcontrol2_texteditor LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/quickcontrols2/texteditor")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Quick QuickControls2 OPTIONAL_COMPONENTS Widgets)

qt_add_executable(${PROJECT_NAME} WIN32 MACOSX_BUNDLE
    documenthandler.cpp
    texteditor.cpp
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Quick
    Qt::QuickControls2
)

# Resources:
set(texteditor_resource_files
    "+touch/texteditor.html"
    "fonts/fontello.ttf"
    "images/qt-logo.png"
    "qml/+touch/texteditor.qml"
    "qml/texteditor.qml"
    "texteditor.html"
)

qt6_add_resources(${PROJECT_NAME} "texteditor"
    PREFIX
        "/"
    FILES
        ${texteditor_resource_files}
)

if(TARGET Qt::Widgets)
    target_link_libraries(${PROJECT_NAME} PUBLIC
        Qt::Widgets
    )
endif()

if(CMAKE_CROSSCOMPILING)
    target_compile_definitions(${PROJECT_NAME} PUBLIC
        QT_EXTRA_FILE_SELECTOR="touch"
    )
endif()

install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
