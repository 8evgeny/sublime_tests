cmake_minimum_required(VERSION 3.16)
project(extension LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/widgets/dialogs/extension")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

qt_add_executable(extension
    finddialog.cpp finddialog.h
    main.cpp
)

set_target_properties(extension PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(extension PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Widgets
)

install(TARGETS extension
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
