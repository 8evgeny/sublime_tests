cmake_minimum_required(VERSION 3.16)
project(toplevel LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/widgets/tutorials/widgets/toplevel")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

qt_add_executable(toplevel
    main.cpp
)

set_target_properties(toplevel PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(toplevel PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Widgets
)

install(TARGETS toplevel
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
