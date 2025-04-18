cmake_minimum_required(VERSION 3.16)
project(sharedmemory LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/corelib/ipc/sharedmemory")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

qt_add_executable(sharedmemory
    dialog.cpp dialog.h dialog.ui
    main.cpp
)

set_target_properties(sharedmemory PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(sharedmemory PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Widgets
)

install(TARGETS sharedmemory
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
