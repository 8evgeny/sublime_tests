cmake_minimum_required(VERSION 3.16)
project(minimal-cpp LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/wayland/minimal-cpp")

find_package(Qt6 REQUIRED COMPONENTS Core Gui WaylandCompositor)

qt_add_executable(minimal-cpp
    compositor.cpp compositor.h
    main.cpp
    window.cpp window.h
)

set_target_properties(minimal-cpp PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_include_directories(minimal-cpp PUBLIC
    ../../include
)

target_link_libraries(minimal-cpp PUBLIC
    # Remove: L
    #../../lib
    Qt::Core
    Qt::Gui
    Qt::WaylandCompositor
)

install(TARGETS minimal-cpp
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
