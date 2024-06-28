file(GLOB src main.cpp)

add_executable(cltest ${src})
target_link_libraries(cltest
    ${OpenCL_LIBRARY}
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    )



