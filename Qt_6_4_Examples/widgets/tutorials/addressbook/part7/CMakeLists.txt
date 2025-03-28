cmake_minimum_required(VERSION 3.16)
project(part7 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/widgets/tutorials/addressbook/part7")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

qt_add_executable(part7
    addressbook.cpp addressbook.h
    finddialog.cpp finddialog.h
    main.cpp
)

set_target_properties(part7 PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(part7 PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Widgets
)

install(TARGETS part7
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
