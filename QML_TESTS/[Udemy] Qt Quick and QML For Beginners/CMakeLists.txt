cmake_minimum_required(VERSION 3.16)

set(PROJECT "Udemi_QML")
project(${PROJECT})
find_package(Qt5 COMPONENTS Widgets Qml Quick REQUIRED)

include_directories(${Qt5Widgets_INCLUDE_DIRS} ${QtQml_INCLUDE_DIRS})
add_definitions(${Qt5Widgets_DEFINITIONS} ${QtQml_DEFINITIONS} ${${Qt5Quick_DEFINITIONS}})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -std=c++17 -fstrict-aliasing -pedantic-errors -pedantic -Wno-deprecated-declarations -Wno-unused-variable")

set(dir1 "2-1QMLSyntaxDemo")
qt5_add_resources(QT_RESOURCES ${dir1}/qml.qrc)
add_executable(${PROJECT}_${dir1}  ${dir1}/main.cpp ${QT_RESOURCES} )
target_link_libraries(${PROJECT}_${dir1} Qt5::Widgets Qt5::Qml Qt5::Quick )

set(dir2 "2-2QMLDataTypesDemo")
qt5_add_resources(QT_RESOURCES  ${dir2}/qml.qrc)
add_executable(${PROJECT}_${dir2}  ${dir2}/main.cpp ${QT_RESOURCES} )
target_link_libraries(${PROJECT}_${dir2} Qt5::Widgets Qt5::Qml Qt5::Quick )

set(dir3 "2-3PropertyBindingDemo")
qt5_add_resources(QT_RESOURCES  ${dir3}/qml.qrc)
add_executable(${PROJECT}_${dir3}  ${dir3}/main.cpp ${QT_RESOURCES} )
target_link_libraries(${PROJECT}_${dir3} Qt5::Widgets Qt5::Qml Qt5::Quick )
