cmake_minimum_required(VERSION 3.5)

project(Chapter1)
find_package(Qt5Widgets REQUIRED)

set(SOURCES QtSimple.cpp)
qt5_wrap_cpp(SOURCES  QtSimple.h)

add_executable(${PROJECT_NAME}_1_SimpleWin SimpleWin.cpp)
add_executable(${PROJECT_NAME}_2_QtSimple ${SOURCES})

set_target_properties(
    ${PROJECT_NAME}_1_SimpleWin
    ${PROJECT_NAME}_2_QtSimple
    PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
    )

target_link_libraries(${PROJECT_NAME}_1_SimpleWin
    -L/usr/X11R6/lib
    -lX11)

target_link_libraries(${PROJECT_NAME}_2_QtSimple
    Qt5::Core
    Qt5::Widgets
    ${Qt5Widgets_LIBRARIES}
    -L/usr/X11R6/lib
    -lX11)
