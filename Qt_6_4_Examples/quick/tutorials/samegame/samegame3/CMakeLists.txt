cmake_minimum_required(VERSION 3.16)
project(samegame3 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/quick/tutorials/samegame/samegame3")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick)

qt_add_executable(samegame3
    main.cpp
)

set_target_properties(samegame3 PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

qt_add_qml_module(samegame3
    URI samegame
    VERSION 1.0
    QML_FILES
        "Block.qml"
        "Button.qml"
        "Dialog.qml"
        "samegame.qml"
        "samegame.js"
    RESOURCES
        "pics/background.jpg"
        "pics/blueStone.png"
        "pics/greenStone.png"
        "pics/redStone.png"
)

target_link_libraries(samegame3 PRIVATE
    Qt::Core
    Qt::Gui
    Qt::Qml
    Qt::Quick
)

install(TARGETS samegame3
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
