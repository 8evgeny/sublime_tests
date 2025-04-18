cmake_minimum_required(VERSION 3.16)
project(quickcontrol2_musicplayer LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/quickcontrols2/imagine/musicplayer")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Quick QuickControls2)

qt_add_executable(${PROJECT_NAME}
    musicplayer.cpp
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Quick
    Qt::QuickControls2
)

# Resources:
set(icons_resource_files
    "icons/musicplayer/32x32/bluetooth.png"
    "icons/musicplayer/32x32/cart.png"
    "icons/musicplayer/32x32/cloud.png"
    "icons/musicplayer/32x32/favorite.png"
    "icons/musicplayer/32x32/filter.png"
    "icons/musicplayer/32x32/folder.png"
    "icons/musicplayer/32x32/message.png"
    "icons/musicplayer/32x32/music.png"
    "icons/musicplayer/32x32/next.png"
    "icons/musicplayer/32x32/pause.png"
    "icons/musicplayer/32x32/power.png"
    "icons/musicplayer/32x32/previous.png"
    "icons/musicplayer/32x32/repeat.png"
    "icons/musicplayer/32x32/save.png"
    "icons/musicplayer/32x32/settings.png"
    "icons/musicplayer/32x32/shuffle.png"
    "icons/musicplayer/32x32/stop.png"
    "icons/musicplayer/32x32@2/bluetooth.png"
    "icons/musicplayer/32x32@2/cart.png"
    "icons/musicplayer/32x32@2/cloud.png"
    "icons/musicplayer/32x32@2/favorite.png"
    "icons/musicplayer/32x32@2/filter.png"
    "icons/musicplayer/32x32@2/folder.png"
    "icons/musicplayer/32x32@2/grid.png"
    "icons/musicplayer/32x32@2/message.png"
    "icons/musicplayer/32x32@2/music.png"
    "icons/musicplayer/32x32@2/next.png"
    "icons/musicplayer/32x32@2/pause.png"
    "icons/musicplayer/32x32@2/power.png"
    "icons/musicplayer/32x32@2/previous.png"
    "icons/musicplayer/32x32@2/repeat.png"
    "icons/musicplayer/32x32@2/save.png"
    "icons/musicplayer/32x32@2/settings.png"
    "icons/musicplayer/32x32@2/shuffle.png"
    "icons/musicplayer/32x32@2/stop.png"
    "icons/musicplayer/index.theme"
)

qt6_add_resources(${PROJECT_NAME} "icons"
    PREFIX
        "/icons"
    BASE
        "icons"
    FILES
        ${icons_resource_files}
)

set(imagine-assets_resource_files
    "imagine-assets/applicationwindow-background.png"
    "imagine-assets/button-background-checked-hovered.9.png"
    "imagine-assets/button-background-checked-hovered@2x.9.png"
    "imagine-assets/button-background-checked.9.png"
    "imagine-assets/button-background-checked@2x.9.png"
    "imagine-assets/button-background-disabled.9.png"
    "imagine-assets/button-background-disabled@2x.9.png"
    "imagine-assets/button-background-hovered.9.png"
    "imagine-assets/button-background-hovered@2x.9.png"
    "imagine-assets/button-background-pressed.9.png"
    "imagine-assets/button-background-pressed@2x.9.png"
    "imagine-assets/button-background.9.png"
    "imagine-assets/button-background@2x.9.png"
    "imagine-assets/combobox-background-hovered.9.png"
    "imagine-assets/combobox-background-hovered@2x.9.png"
    "imagine-assets/combobox-background-open.9.png"
    "imagine-assets/combobox-background-open@2x.9.png"
    "imagine-assets/combobox-background-pressed.9.png"
    "imagine-assets/combobox-background-pressed@2x.9.png"
    "imagine-assets/combobox-background.9.png"
    "imagine-assets/combobox-background@2x.9.png"
    "imagine-assets/combobox-indicator-hovered.png"
    "imagine-assets/combobox-indicator-hovered@2x.png"
    "imagine-assets/combobox-indicator-open.png"
    "imagine-assets/combobox-indicator-open@2x.png"
    "imagine-assets/combobox-indicator-pressed.png"
    "imagine-assets/combobox-indicator-pressed@2x.png"
    "imagine-assets/combobox-indicator.png"
    "imagine-assets/combobox-indicator@2x.png"
    "imagine-assets/combobox-popup.9.png"
    "imagine-assets/combobox-popup@2x.9.png"
    "imagine-assets/dial-background-hovered.png"
    "imagine-assets/dial-background-hovered@2x.png"
    "imagine-assets/dial-background-pressed.png"
    "imagine-assets/dial-background-pressed@2x.png"
    "imagine-assets/dial-background.png"
    "imagine-assets/dial-background@2x.png"
    "imagine-assets/dial-handle-pressed.png"
    "imagine-assets/dial-handle-pressed@2x.png"
    "imagine-assets/dial-handle.png"
    "imagine-assets/dial-handle@2x.png"
    "imagine-assets/frame-background.9.png"
    "imagine-assets/frame-background@2x.9.png"
    "imagine-assets/itemdelegate-background-checked.9.png"
    "imagine-assets/itemdelegate-background-checked@2x.9.png"
    "imagine-assets/itemdelegate-background-disabled.9.png"
    "imagine-assets/itemdelegate-background-disabled@2x.9.png"
    "imagine-assets/itemdelegate-background-hovered.9.png"
    "imagine-assets/itemdelegate-background-hovered@2x.9.png"
    "imagine-assets/itemdelegate-background-pressed.9.png"
    "imagine-assets/itemdelegate-background-pressed@2x.9.png"
    "imagine-assets/itemdelegate-background.9.png"
    "imagine-assets/itemdelegate-background@2x.9.png"
    "imagine-assets/roundbutton-background-checked-hovered.png"
    "imagine-assets/roundbutton-background-checked-hovered@2x.png"
    "imagine-assets/roundbutton-background-checked.png"
    "imagine-assets/roundbutton-background-checked@2x.png"
    "imagine-assets/roundbutton-background-disabled.png"
    "imagine-assets/roundbutton-background-disabled@2x.png"
    "imagine-assets/roundbutton-background-hovered.png"
    "imagine-assets/roundbutton-background-hovered@2x.png"
    "imagine-assets/roundbutton-background-pressed.png"
    "imagine-assets/roundbutton-background-pressed@2x.png"
    "imagine-assets/roundbutton-background.png"
    "imagine-assets/roundbutton-background@2x.png"
    "imagine-assets/scrollbar-handle-interactive-hovered.png"
    "imagine-assets/scrollbar-handle-interactive-hovered@2x.png"
    "imagine-assets/scrollbar-handle-interactive-pressed.png"
    "imagine-assets/scrollbar-handle-interactive-pressed@2x.png"
    "imagine-assets/scrollbar-handle-interactive.png"
    "imagine-assets/scrollbar-handle-interactive@2x.png"
    "imagine-assets/slider-background-horizontal-disabled.9.png"
    "imagine-assets/slider-background-horizontal-disabled@2x.9.png"
    "imagine-assets/slider-background-horizontal.9.png"
    "imagine-assets/slider-background-horizontal@2x.9.png"
    "imagine-assets/slider-background-vertical-disabled.9.png"
    "imagine-assets/slider-background-vertical-disabled@2x.9.png"
    "imagine-assets/slider-background-vertical.9.png"
    "imagine-assets/slider-background-vertical@2x.9.png"
    "imagine-assets/slider-handle-disabled.png"
    "imagine-assets/slider-handle-disabled@2x.png"
    "imagine-assets/slider-handle-hovered.png"
    "imagine-assets/slider-handle-hovered@2x.png"
    "imagine-assets/slider-handle.png"
    "imagine-assets/slider-handle@2x.png"
    "imagine-assets/slider-progress-horizontal.9.png"
    "imagine-assets/slider-progress-horizontal@2x.9.png"
    "imagine-assets/slider-progress-vertical-disabled.9.png"
    "imagine-assets/slider-progress-vertical-disabled@2x.9.png"
    "imagine-assets/slider-progress-vertical.9.png"
    "imagine-assets/slider-progress-vertical@2x.9.png"
    "imagine-assets/textfield-background-disabled.9.png"
    "imagine-assets/textfield-background-disabled@2x.9.png"
    "imagine-assets/textfield-background.9.png"
    "imagine-assets/textfield-background@2x.9.png"
    "imagine-assets/toolbar-background.9.png"
    "imagine-assets/toolbar-background@2x.9.png"
    "imagine-assets/toolbutton-background-checked-hovered.9.png"
    "imagine-assets/toolbutton-background-checked-hovered@2x.9.png"
    "imagine-assets/toolbutton-background-checked.9.png"
    "imagine-assets/toolbutton-background-checked@2x.9.png"
    "imagine-assets/toolbutton-background-hovered.9.png"
    "imagine-assets/toolbutton-background-hovered@2x.9.png"
    "imagine-assets/toolbutton-background-pressed.9.png"
    "imagine-assets/toolbutton-background-pressed@2x.9.png"
    "imagine-assets/toolbutton-background.9.png"
    "imagine-assets/toolbutton-background@2x.9.png"
    "imagine-assets/tooltip-background.9.png"
    "imagine-assets/tooltip-background@2x.9.png"
)

qt6_add_resources(${PROJECT_NAME} "imagine-assets"
    PREFIX
        "/imagine-assets"
    BASE
        "imagine-assets"
    FILES
        ${imagine-assets_resource_files}
)

set(qmake_immediate_resource_files
    "images/album-cover.jpg"
    "musicplayer.qml"
    "qtquickcontrols2.conf"
)

qt6_add_resources(${PROJECT_NAME} "qmake_immediate"
    PREFIX
        "/"
    FILES
        ${qmake_immediate_resource_files}
)

install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
