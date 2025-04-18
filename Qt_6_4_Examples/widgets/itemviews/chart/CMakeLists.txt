cmake_minimum_required(VERSION 3.16)
project(chart LANGUAGES CXX)
set(CMAKE_PREFIX_PATH "/home/evg/Qt6_4/6.4.0/gcc_64")
set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/widgets/itemviews/chart")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

qt_add_executable(chart
    main.cpp
    mainwindow.cpp mainwindow.h
    pieview.cpp pieview.h
)

set_target_properties(chart PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(chart PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Widgets
)

# Resources:
set(chart_resource_files
    "qtdata.cht"
)

qt_add_resources(chart "chart"
    PREFIX
        "/Charts"
    FILES
        ${chart_resource_files}
)

if(UNIX AND NOT APPLE AND NOT HAIKU AND NOT INTEGRITY AND NOT VXWORKS)
    target_link_libraries(chart PUBLIC
        m
    )
endif()

install(TARGETS chart
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
