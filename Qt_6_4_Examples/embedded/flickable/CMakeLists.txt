cmake_minimum_required(VERSION 3.16)
project(flickable LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/embedded/flickable")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

qt_add_executable(flickable
    flickable.cpp flickable.h
    main.cpp
)

set_target_properties(flickable PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(flickable PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Widgets
)

install(TARGETS flickable
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
