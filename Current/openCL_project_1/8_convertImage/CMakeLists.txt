file(GLOB src
    main.cpp
    )

add_executable(8_comvertImage ${src})
target_link_libraries(8_comvertImage
    ${OpenCL_LIBRARY}
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    ${OpenCV_LIBS}
    )
configure_file(kernel.cl ${CMAKE_CURRENT_BINARY_DIR}/kernel COPYONLY)

configure_file(Lena.png ${CMAKE_CURRENT_BINARY_DIR}/image COPYONLY)


