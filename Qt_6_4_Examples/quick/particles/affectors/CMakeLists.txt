cmake_minimum_required(VERSION 3.16)
project(affectors LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/quick/particles/affectors")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick)

add_subdirectory("../../shared" "shared")

qt_add_executable(affectorsexample WIN32 MACOSX_BUNDLE
    main.cpp
)

target_link_libraries(affectorsexample PRIVATE
    Qt::Core
    Qt::Gui
    Qt::Qml
    Qt::Quick
)

add_dependencies(affectorsexample affectors_shared)

# Resources:
qt_add_qml_module(affectorsexample
    URI affectors
    VERSION 1.0
    QML_FILES
        "affectors.qml"
        "GreyButton.qml"
        "age.qml"
        "attractor.qml"
        "customaffector.qml"
        "friction.qml"
        "gravity.qml"
        "groupgoal.qml"
        "move.qml"
        "spritegoal.qml"
        "turbulence.qml"
        "wander.qml"
    RESOURCES
        "images/snowflake.png"
        "images/finalfrontier.png"
        "images/meteor.png"
        "images/rocket.png"
        "images/rocket2.png"
        "images/backgroundLeaves.jpg"
        "images/realLeaf1.png"
        "images/realLeaf2.png"
        "images/realLeaf3.png"
        "images/realLeaf4.png"
        "images/particleA.png"
        "images/matchmask.png"
        "images/nullRock.png"
        "images/_explo.png"
        "images/candle.png"
)

install(TARGETS affectorsexample
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)

bundle_shared(affectorsexample)
