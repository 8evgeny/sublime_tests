cmake_minimum_required(VERSION 3.16)
project(styleexample LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/embedded/styleexample")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

qt_add_executable(styleexample
    main.cpp
    stylewidget.cpp stylewidget.h stylewidget.ui
)

set_target_properties(styleexample PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(styleexample PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Widgets
)

# Resources:
set(styleexample_resource_files
    "files/add.png"
    "files/application.qss"
    "files/blue.qss"
    "files/khaki.qss"
    "files/nature_1.jpg"
    "files/nostyle.qss"
    "files/remove.png"
    "files/transparent.qss"
)

qt_add_resources(styleexample "styleexample"
    PREFIX
        "/"
    FILES
        ${styleexample_resource_files}
)

install(TARGETS styleexample
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
