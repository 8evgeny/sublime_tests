cmake_minimum_required(VERSION 3.16)
project(cachedtable LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/sql/cachedtable")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Sql Widgets)

qt_add_executable(cachedtable
    ../connection.h
    main.cpp
    tableeditor.cpp tableeditor.h
)

set_target_properties(cachedtable PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(cachedtable PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Sql
    Qt::Widgets
)

install(TARGETS cachedtable
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
