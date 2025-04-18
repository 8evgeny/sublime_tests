cmake_minimum_required(VERSION 3.16)
project(pointerhandlers LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/quick/pointerhandlers")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick Svg)

add_subdirectory("../shared" "shared")

qt_add_executable(pointerhandlersexample WIN32 MACOSX_BUNDLE main.cpp)

target_link_libraries(pointerhandlersexample PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Qml
    Qt::Quick
    Qt::Svg
)

add_dependencies(pointerhandlersexample pointerhandlers_shared)

qt_add_qml_module(pointerhandlersexample
    URI pointerhandlers
    VERSION 1.0
    QML_FILES
        "components/Button.qml"
        "components/CheckBox.qml"
        "components/FakeFlickable.qml"
        "components/FlashAnimation.qml"
        "components/LeftDrawer.qml"
        "components/MomentumAnimation.qml"
        "components/MouseFeedbackSprite.qml"
        "components/QuadPieMenu.qml"
        "components/ScrollBar.qml"
        "components/Slider.qml"
        "components/TouchpointFeedbackSprite.qml"
        "fakeFlickable.qml"
        "flingAnimation.qml"
        "joystick.qml"
        "map.qml"
        "mixer.qml"
        "multibuttons.qml"
        "pieMenu.qml"
        "pinchHandler.qml"
        "pointerhandlers.qml"
        "sidebar.qml"
        "singlePointHandlerProperties.qml"
        "tabletCanvasDrawing.qml"
        "tapHandler.qml"
    RESOURCES
        "components/images/checkmark.png"
        "components/images/fingersprite.png"
        "components/images/mixer-knob.png"
        "components/images/mouse.png"
        "components/images/mouse_left.png"
        "components/images/mouse_middle.png"
        "components/images/mouse_right.png"
        "components/images/mouse_wheel_ridges.png"
        "images/arrowhead.png"
        "images/balloon.png"
        "images/cursor-airbrush.png"
        "images/cursor-eraser.png"
        "images/cursor-felt-marker.png"
        "images/cursor-pencil.png"
        "images/fighter.png"
        "images/grabbing-location.svg"
        "images/joystick-outer-case-pov.jpg"
        "images/map.svgz"
        "images/missile.png"
        "images/redball.png"
)

install(TARGETS pointerhandlersexample
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)

bundle_shared(pointerhandlersexample)
