cmake_minimum_required(VERSION 3.16)
project(easing LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/widgets/animation/easing")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

qt_add_executable(easing
    animation.h
    form.ui
    main.cpp
    window.cpp window.h
)

set_target_properties(easing PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(easing PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Widgets
)

# Resources:
set(easing_resource_files
    "images/qt-logo.png"
)

qt_add_resources(easing "easing"
    PREFIX
        "/"
    FILES
        ${easing_resource_files}
)

install(TARGETS easing
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
