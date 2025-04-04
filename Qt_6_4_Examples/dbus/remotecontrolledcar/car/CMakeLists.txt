cmake_minimum_required(VERSION 3.16)
project(car LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/dbus/remotecontrolledcar/car")

find_package(Qt6 REQUIRED COMPONENTS Core DBus Gui Widgets)

set(car_SRCS)
qt_add_dbus_adaptor(car_SRCS
    car.xml
    qobject.h
    "" # empty parent_class value on purpose to not pass -l flag
    car_adaptor
)

qt_add_executable(car
    car.cpp car.h
    main.cpp
    ${car_SRCS}
)

set_target_properties(car PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(car PUBLIC
    Qt::Core
    Qt::DBus
    Qt::Gui
    Qt::Widgets
)

install(TARGETS car
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
