cmake_minimum_required(VERSION 3.16)
project(syntaxhighlighter LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/widgets/richtext/syntaxhighlighter")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

qt_add_executable(syntaxhighlighter
    highlighter.cpp highlighter.h
    main.cpp
    mainwindow.cpp mainwindow.h
)

set_target_properties(syntaxhighlighter PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(syntaxhighlighter PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Widgets
)

install(TARGETS syntaxhighlighter
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
