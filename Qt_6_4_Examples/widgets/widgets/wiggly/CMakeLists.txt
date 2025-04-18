cmake_minimum_required(VERSION 3.16)
project(wiggly LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/widgets/widgets/wiggly")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

qt_add_executable(wiggly
    dialog.cpp dialog.h
    main.cpp
    wigglywidget.cpp wigglywidget.h
)

set_target_properties(wiggly PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(wiggly PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Widgets
)

install(TARGETS wiggly
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
