cmake_minimum_required(VERSION 3.16)
project(quickcontrol2_chapter3 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/quickcontrols2/chattutorial/chapter3")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick)

qt_add_executable(${PROJECT_NAME} WIN32 MACOSX_BUNDLE
    main.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt::Core
    Qt::Gui
    Qt::Qml
    Qt::Quick
)

# Resources:
qt_add_qml_module(${PROJECT_NAME}
    URI chapter3
    VERSION 1.0
    QML_FILES
        "ContactPage.qml"
        "ConversationPage.qml"
        "main.qml"
    RESOURCES
        "images/Albert_Einstein.png"
        "images/Albert_Einstein@2x.png"
        "images/Albert_Einstein@3x.png"
        "images/Albert_Einstein@4x.png"
        "images/Ernest_Hemingway.png"
        "images/Ernest_Hemingway@2x.png"
        "images/Ernest_Hemingway@3x.png"
        "images/Ernest_Hemingway@4x.png"
        "images/Hans_Gude.png"
        "images/Hans_Gude@2x.png"
        "images/Hans_Gude@3x.png"
        "images/Hans_Gude@4x.png"
)

qt6_add_resources(${PROJECT_NAME} "conf"
    PREFIX
        "/"
    FILES
        "qtquickcontrols2.conf"
)

install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
