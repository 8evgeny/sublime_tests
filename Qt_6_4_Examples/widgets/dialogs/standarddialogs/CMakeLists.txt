cmake_minimum_required(VERSION 3.16)
project(standarddialogs LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/widgets/dialogs/standarddialogs")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

qt_add_executable(standarddialogs
    dialog.cpp dialog.h
    main.cpp
)

set_target_properties(standarddialogs PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(standarddialogs PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Widgets
)

install(TARGETS standarddialogs
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
