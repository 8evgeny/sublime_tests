cmake_minimum_required(VERSION 3.16)
project(storageview LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/widgets/itemviews/storageview")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

qt_add_executable(storageview
    main.cpp
    storagemodel.cpp storagemodel.h
)

set_target_properties(storageview PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(storageview PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Widgets
)

install(TARGETS storageview
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
