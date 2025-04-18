cmake_minimum_required(VERSION 3.16)
project(quickcontrol2_eventcalendar LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/quickcontrols2/eventcalendar")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Sql)

qt_add_executable(${PROJECT_NAME}
    event.h
    eventcalendar.cpp
    eventmodel.cpp eventmodel.h
    sqleventdatabase.cpp sqleventdatabase.h
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Qml
    Qt::Sql
)

qt_add_qml_module(${PROJECT_NAME}
    URI App
    VERSION 1.0
    QML_FILES
        MonthGridDelegate.qml
        eventcalendar.qml
    RESOURCES
        qtquickcontrols2.conf
    NO_RESOURCE_TARGET_PATH
)

install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
