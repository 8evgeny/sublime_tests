cmake_minimum_required(VERSION 3.16)
project(drilldown LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/sql/drilldown")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Sql Widgets)

qt_add_executable(drilldown
    ../connection.h
    imageitem.cpp imageitem.h
    informationwindow.cpp informationwindow.h
    main.cpp
    view.cpp view.h
)

set_target_properties(drilldown PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(drilldown PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Sql
    Qt::Widgets
)

# Resources:
set(drilldown_resource_files
    "images/qt-creator.png"
    "images/qt-logo.png"
    "images/qt-project.png"
    "images/qt-quick.png"
)

qt_add_resources(drilldown "drilldown"
    PREFIX
        "/"
    FILES
        ${drilldown_resource_files}
)

install(TARGETS drilldown
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
