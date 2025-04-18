cmake_minimum_required(VERSION 3.16)
project(calculatorbuilder LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/designer/calculatorbuilder")

find_package(Qt6 REQUIRED COMPONENTS Core Gui UiTools Widgets)

qt_add_executable(calculatorbuilder
    calculatorform.cpp calculatorform.h
    main.cpp
)

set_target_properties(calculatorbuilder PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(calculatorbuilder PUBLIC
    Qt::Core
    Qt::Gui
    Qt::UiTools
    Qt::Widgets
)

# Resources:
set(calculatorbuilder_resource_files
    "calculatorform.ui"
)

qt6_add_resources(calculatorbuilder "calculatorbuilder"
    PREFIX
        "/forms"
    FILES
        ${calculatorbuilder_resource_files}
)

install(TARGETS calculatorbuilder
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
