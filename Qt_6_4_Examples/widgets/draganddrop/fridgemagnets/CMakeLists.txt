cmake_minimum_required(VERSION 3.16)
project(fridgemagnets LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/widgets/draganddrop/fridgemagnets")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

qt_add_executable(fridgemagnets
    draglabel.cpp draglabel.h
    dragwidget.cpp dragwidget.h
    main.cpp
)

set_target_properties(fridgemagnets PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(fridgemagnets PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Widgets
)

# Resources:
set(fridgemagnets_resource_files
    "words.txt"
)

qt_add_resources(fridgemagnets "fridgemagnets"
    PREFIX
        "/dictionary"
    FILES
        ${fridgemagnets_resource_files}
)

install(TARGETS fridgemagnets
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
