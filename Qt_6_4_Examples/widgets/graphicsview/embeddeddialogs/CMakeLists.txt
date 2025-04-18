cmake_minimum_required(VERSION 3.16)
project(embeddeddialogs LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/widgets/graphicsview/embeddeddialogs")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

qt_add_executable(embeddeddialogs
    customproxy.cpp customproxy.h
    embeddeddialog.cpp embeddeddialog.h embeddeddialog.ui
    main.cpp
)

set_target_properties(embeddeddialogs PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(embeddeddialogs PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Widgets
)

# Resources:
set(embeddeddialogs_resource_files
    "No-Ones-Laughing-3.jpg"
)

qt_add_resources(embeddeddialogs "embeddeddialogs"
    PREFIX
        "/"
    FILES
        ${embeddeddialogs_resource_files}
)

install(TARGETS embeddeddialogs
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
