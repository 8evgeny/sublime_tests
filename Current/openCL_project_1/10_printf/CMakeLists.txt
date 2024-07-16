file(GLOB src
    printf.cpp
    )

add_executable(10_printf ${src})
target_link_libraries(10_printf
    ${OpenCL_LIBRARY}
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    ${OpenCV_LIBS}
    )
configure_file(printf.cl ${CMAKE_CURRENT_BINARY_DIR}/printf.cl COPYONLY)




