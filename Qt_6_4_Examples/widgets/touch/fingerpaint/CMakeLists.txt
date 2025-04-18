cmake_minimum_required(VERSION 3.16)
project(fingerpaint LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/widgets/touch/fingerpaint")

find_package(Qt6
    REQUIRED COMPONENTS Core Gui Widgets
    OPTIONAL_COMPONENTS PrintSupport
)

qt_add_executable(fingerpaint
    main.cpp
    mainwindow.cpp mainwindow.h
    scribblearea.cpp scribblearea.h
)

set_target_properties(fingerpaint PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(fingerpaint PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Widgets
)

if (TARGET Qt::PrintSupport)
    target_link_libraries(fingerpaint PUBLIC Qt::PrintSupport)
endif()

if(TARGET Qt::PrintSupport)
    target_link_libraries(fingerpaint PUBLIC
        Qt::PrintSupport
    )
endif()

install(TARGETS fingerpaint
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
