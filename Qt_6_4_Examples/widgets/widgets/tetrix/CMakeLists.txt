cmake_minimum_required(VERSION 3.16)
project(tetrix LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/widgets/widgets/tetrix")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

qt_add_executable(tetrix
    main.cpp
    tetrixboard.cpp tetrixboard.h
    tetrixpiece.cpp tetrixpiece.h
    tetrixwindow.cpp tetrixwindow.h
)

set_target_properties(tetrix PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(tetrix PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Widgets
)

install(TARGETS tetrix
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
