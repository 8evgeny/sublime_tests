cmake_minimum_required(VERSION 3.16)
project(pixelator LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/widgets/itemviews/pixelator")

find_package(Qt6
    REQUIRED COMPONENTS Core Gui Widgets
    OPTIONAL_COMPONENTS PrintSupport
)

qt_add_executable(pixelator
    imagemodel.cpp imagemodel.h
    main.cpp
    mainwindow.cpp mainwindow.h
    pixeldelegate.cpp pixeldelegate.h
)

set_target_properties(pixelator PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(pixelator PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Widgets
)

# Resources:
set(images_resource_files
    "images/qt.png"
)

qt_add_resources(pixelator "images"
    PREFIX
        "/"
    FILES
        ${images_resource_files}
)

if(TARGET Qt::PrintSupport)
    target_link_libraries(pixelator PUBLIC
        Qt::PrintSupport
    )
endif()

install(TARGETS pixelator
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
