cmake_minimum_required(VERSION 3.16)
project(elasticnodes LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/widgets/graphicsview/elasticnodes")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

qt_add_executable(elasticnodes
    edge.cpp edge.h
    graphwidget.cpp graphwidget.h
    main.cpp
    node.cpp node.h
)

set_target_properties(elasticnodes PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(elasticnodes PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Widgets
)

install(TARGETS elasticnodes
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
