cmake_minimum_required(VERSION 3.16)
project(photosurface LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/demos/photosurface")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick)

if (WIN32)
#! [appicon_windows]
    set(app_icon_resource_windows "${CMAKE_CURRENT_SOURCE_DIR}/resources/photosurface.rc")
    qt_add_executable(photosurface main.cpp ${app_icon_resource_windows})
#! [appicon_windows]
elseif (APPLE)
#! [appicon_macOS]
    # The MACOSX_BUNDLE_ICON_FILE variable is added to the Info.plist
    # generated by CMake. This variable contains the .icns file name,
    # without the path.
    set(MACOSX_BUNDLE_ICON_FILE photosurface.icns)

    # And the following tells CMake where to find and install the file itself.
    set(app_icon_macos "${CMAKE_CURRENT_SOURCE_DIR}/resources/photosurface.icns")
    set_source_files_properties(${app_icon_macos} PROPERTIES
           MACOSX_PACKAGE_LOCATION "Resources")

    qt_add_executable(photosurface MACOSX_BUNDLE main.cpp ${app_icon_macos})
#! [appicon_macOS]
else()
    qt_add_executable(photosurface main.cpp)
endif()

target_link_libraries(photosurface PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Qml
    Qt::Quick
)

# Resources:
set(photosurface_resource_files
    "photosurface.qml"
    "resources/folder.png"
)

qt6_add_resources(photosurface "photosurface"
    PREFIX
        "/"
    FILES
        ${photosurface_resource_files}
)

if(TARGET Qt::Widgets)
    target_link_libraries(photosurface PUBLIC
        Qt::Widgets
    )
endif()

install(TARGETS photosurface
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
