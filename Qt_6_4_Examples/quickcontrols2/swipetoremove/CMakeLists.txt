cmake_minimum_required(VERSION 3.16)
project(quickcontrol2_swipetoremove LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/quickcontrols2/swipetoremove")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml)

qt_add_executable(${PROJECT_NAME}
    swipetoremove.cpp
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Qml
)

# Resources:
set(qmake_immediate_resource_files
    "fonts/fontello.ttf"
    "swipetoremove.qml"
)

qt6_add_resources(${PROJECT_NAME} "qmake_immediate"
    PREFIX
        "/"
    FILES
        ${qmake_immediate_resource_files}
)

install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
