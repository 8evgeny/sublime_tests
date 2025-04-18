cmake_minimum_required(VERSION 3.16)
project(progressdialog LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/qtconcurrent/progressdialog")

find_package(Qt6 REQUIRED COMPONENTS Concurrent Core Gui Widgets)

qt_add_executable(progressdialog
    main.cpp
)

set_target_properties(progressdialog PROPERTIES
    WIN32_EXECUTABLE FALSE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(progressdialog PUBLIC
    Qt::Concurrent
    Qt::Core
    Qt::Gui
    Qt::Widgets
)

install(TARGETS progressdialog
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
