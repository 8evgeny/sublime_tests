cmake_minimum_required(VERSION 3.16)
project(download LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/network/download")

find_package(Qt6 REQUIRED COMPONENTS Core Network)

qt_add_executable(download
    main.cpp
)

target_link_libraries(download PUBLIC
    Qt::Core
    Qt::Network
)

install(TARGETS download
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
