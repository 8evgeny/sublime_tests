cmake_minimum_required(VERSION 3.16)
project(dialcontrol LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/quick/customitems/dialcontrol")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick)

qt_add_executable(dialcontrolexample
    main.cpp
)

set_target_properties(dialcontrolexample PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(dialcontrolexample PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Qml
    Qt::Quick
)

qt_add_qml_module(dialcontrolexample
    URI dialcontrol
    VERSION 1.0
    QML_FILES
        "Dial.qml"
        "QuitButton.qml"
        "dialcontrol.qml"
    RESOURCES
        "background.png"
        "needle.png"
        "needle_shadow.png"
        "overlay.png"
        "quit.png"
)

install(TARGETS dialcontrolexample
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
