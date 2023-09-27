set(name "Grid_View")
qt5_add_resources(QT_RESOURCES  qml.qrc)
add_executable(${name}  main.cpp ${QT_RESOURCES} )
target_link_libraries(${name} Qt5::Widgets Qt5::Qml Qt5::Quick )

