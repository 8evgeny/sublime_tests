set(name "7-10ProgressBarDemo")
include_directories(${Qt5QuickControls2_INCLUDE_DIRS})
find_package(Qt5 COMPONENTS QuickControls2 REQUIRED)
qt5_add_resources(QT_RESOURCES  qml.qrc)
add_executable(${name}  main.cpp ${QT_RESOURCES} )
target_link_libraries(${name} Qt5::Widgets Qt5::Qml Qt5::Quick Qt5::QuickControls2)

