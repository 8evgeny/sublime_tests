cmake_minimum_required(VERSION 3.16)
project(painterpaths LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/widgets/painting/painterpaths")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

qt_add_executable(painterpaths
    main.cpp
    renderarea.cpp renderarea.h
    window.cpp window.h
)

set_target_properties(painterpaths PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(painterpaths PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Widgets
)

if(UNIX AND NOT APPLE AND NOT HAIKU AND NOT INTEGRITY AND NOT VXWORKS)
    target_link_libraries(painterpaths PUBLIC
        m
    )
endif()

install(TARGETS painterpaths
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
