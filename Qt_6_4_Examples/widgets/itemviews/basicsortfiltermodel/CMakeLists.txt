cmake_minimum_required(VERSION 3.16)
project(basicsortfiltermodel LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/widgets/itemviews/basicsortfiltermodel")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

qt_add_executable(basicsortfiltermodel
    main.cpp
    window.cpp window.h
)

set_target_properties(basicsortfiltermodel PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(basicsortfiltermodel PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Widgets
)

install(TARGETS basicsortfiltermodel
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
