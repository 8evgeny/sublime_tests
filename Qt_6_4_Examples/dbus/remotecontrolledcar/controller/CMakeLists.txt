cmake_minimum_required(VERSION 3.16)
project(controller LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/dbus/remotecontrolledcar/controller")

find_package(Qt6 REQUIRED COMPONENTS Core DBus Gui Widgets)

set(controller_SRCS)
qt_add_dbus_interface(controller_SRCS
    car.xml
    car_interface
)

qt_add_executable(controller
    controller.cpp controller.h controller.ui
    main.cpp
    ${controller_SRCS}
)

set_target_properties(controller PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(controller PUBLIC
    Qt::Core
    Qt::DBus
    Qt::Gui
    Qt::Widgets
)

install(TARGETS controller
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
