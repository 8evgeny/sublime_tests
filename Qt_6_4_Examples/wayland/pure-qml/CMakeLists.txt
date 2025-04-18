cmake_minimum_required(VERSION 3.16)
project(pure-qml LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/wayland/pure-qml")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml)

qt_add_executable(pure-qml
    main.cpp
)

set_target_properties(pure-qml PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(pure-qml PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Qml
)

# Resources:
set(pure-qml_resource_files
    "images/background.jpg"
    "qml/Chrome.qml"
    "qml/CompositorScreen.qml"
    "qml/Keyboard.qml"
    "qml/main.qml"
)

qt6_add_resources(pure-qml "pure-qml"
    PREFIX
        "/"
    FILES
        ${pure-qml_resource_files}
)

install(TARGETS pure-qml
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
