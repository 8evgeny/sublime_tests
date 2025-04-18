cmake_minimum_required(VERSION 3.16)
project(icons LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/widgets/widgets/icons")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

qt_add_executable(icons
    iconpreviewarea.cpp iconpreviewarea.h
    iconsizespinbox.cpp iconsizespinbox.h
    imagedelegate.cpp imagedelegate.h
    main.cpp
    mainwindow.cpp mainwindow.h
)

set_target_properties(icons PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_compile_definitions(icons PUBLIC
    SRCDIR="${CMAKE_CURRENT_SOURCE_DIR}"
)

target_link_libraries(icons PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Widgets
)

install(TARGETS icons
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
