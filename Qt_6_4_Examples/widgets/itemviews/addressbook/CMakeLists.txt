cmake_minimum_required(VERSION 3.16)
project(addressbook LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/widgets/itemviews/addressbook")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

qt_add_executable(addressbook
    adddialog.cpp adddialog.h
    addresswidget.cpp addresswidget.h
    main.cpp
    mainwindow.cpp mainwindow.h
    newaddresstab.cpp newaddresstab.h
    tablemodel.cpp tablemodel.h
)

set_target_properties(addressbook PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(addressbook PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Widgets
)

install(TARGETS addressbook
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
