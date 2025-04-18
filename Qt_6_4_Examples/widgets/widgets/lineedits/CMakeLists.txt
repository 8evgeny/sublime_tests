cmake_minimum_required(VERSION 3.16)
project(lineedits LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/widgets/widgets/lineedits")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

qt_add_executable(lineedits
    main.cpp
    window.cpp window.h
)

set_target_properties(lineedits PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(lineedits PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Widgets
)

install(TARGETS lineedits
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
