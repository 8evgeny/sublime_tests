cmake_minimum_required(VERSION 3.16)
project(samegame4 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/quick/tutorials/samegame/samegame4")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick)

qt_add_executable(samegame4
    main.cpp
)

set_target_properties(samegame4 PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

qt_add_qml_module(samegame4
    URI samegame
    VERSION 1.0
    QML_FILES
        "BoomBlock.qml"
        "Button.qml"
        "Dialog.qml"
        "samegame.qml"
        "samegame.js"
    RESOURCES
        "highscores/README"
        "highscores/score_data.xml"
        "highscores/score_style.xsl"
        "highscores/scores.php"
        "pics/background.jpg"
        "pics/blueStar.png"
        "pics/blueStone.png"
        "pics/greenStar.png"
        "pics/greenStone.png"
        "pics/redStar.png"
        "pics/redStone.png"
)

target_link_libraries(samegame4 PRIVATE
    Qt::Core
    Qt::Gui
    Qt::Qml
    Qt::Quick
)

install(TARGETS samegame4
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
