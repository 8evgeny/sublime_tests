cmake_minimum_required(VERSION 3.16)
project(anchorlayout LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/widgets/graphicsview/anchorlayout")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

qt_add_executable(anchorlayout
    main.cpp
)

set_target_properties(anchorlayout PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(anchorlayout PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Widgets
)

install(TARGETS anchorlayout
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
