cmake_minimum_required(VERSION 3.16)
project(getting_started_part3 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/widgets/tutorials/gettingStarted/gsQt/part3")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

qt_add_executable(getting_started_part3
    main.cpp
)

set_target_properties(getting_started_part3 PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(getting_started_part3 PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Widgets
)

install(TARGETS getting_started_part3
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
