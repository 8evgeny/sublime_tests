cmake_minimum_required(VERSION 3.16)
project(complexpingpong LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/dbus/complexpingpong")

find_package(Qt6 REQUIRED COMPONENTS Core DBus)

qt_add_executable(complexping
    complexping.cpp complexping.h
    ping-common.h
)

target_link_libraries(complexping PRIVATE
    Qt6::Core
    Qt6::DBus
)

qt_add_executable(complexpong
    complexpong.cpp complexpong.h
)

target_link_libraries(complexpong PRIVATE
    Qt6::Core
    Qt6::DBus
)

install(TARGETS complexping complexpong
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
