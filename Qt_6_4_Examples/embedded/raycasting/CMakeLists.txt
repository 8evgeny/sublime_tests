cmake_minimum_required(VERSION 3.16)
project(raycasting LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/embedded/raycasting")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

qt_add_executable(raycasting
    raycasting.cpp
)

set_target_properties(raycasting PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(raycasting PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Widgets
)

# Resources:
set(raycasting_resource_files
    "textures.png"
)

qt_add_resources(raycasting "raycasting"
    PREFIX
        "/"
    FILES
        ${raycasting_resource_files}
)

install(TARGETS raycasting
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
