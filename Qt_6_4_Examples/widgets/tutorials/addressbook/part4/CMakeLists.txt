cmake_minimum_required(VERSION 3.16)
project(part4 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/widgets/tutorials/addressbook/part4")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

qt_add_executable(part4
    addressbook.cpp addressbook.h
    main.cpp
)

set_target_properties(part4 PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(part4 PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Widgets
)

install(TARGETS part4
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
