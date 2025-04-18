cmake_minimum_required(VERSION 3.16)
project(flowlayout LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/widgets/graphicsview_flowlayout")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

qt_add_executable(graphicsview_flowlayout
    flowlayout.cpp flowlayout.h
    main.cpp
    window.cpp window.h
)

set_target_properties(graphicsview_flowlayout PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(graphicsview_flowlayout PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Widgets
)

install(TARGETS graphicsview_flowlayout
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
