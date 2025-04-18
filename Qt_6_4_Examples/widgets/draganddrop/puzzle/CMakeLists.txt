cmake_minimum_required(VERSION 3.16)
project(puzzle LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/widgets/draganddrop_puzzle")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

qt_add_executable(draganddrop_puzzle
    main.cpp
    mainwindow.cpp mainwindow.h
    pieceslist.cpp pieceslist.h
    puzzlewidget.cpp puzzlewidget.h
)

set_target_properties(draganddrop_puzzle PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(draganddrop_puzzle PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Widgets
)

# Resources:
set(puzzle_resource_files
    "example.jpg"
)

qt_add_resources(draganddrop_puzzle "puzzle"
    PREFIX
        "/images"
    FILES
        ${puzzle_resource_files}
)

install(TARGETS draganddrop_puzzle
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
