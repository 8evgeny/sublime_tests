file(GLOB src
    main.cpp
    )

add_executable(3_edge2 ${src})
target_link_libraries(3_edge2
    ${OpenCL_LIBRARY}
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    ${OpenCV_LIBS}
    )
#configure_file(main.cl ${CMAKE_CURRENT_BINARY_DIR}/kernel COPYONLY)
configure_file(copy.cl ${CMAKE_CURRENT_BINARY_DIR}/kernel COPYONLY)
#configure_file(kernel.cl ${CMAKE_CURRENT_BINARY_DIR}/kernel COPYONLY)

configure_file(tank.png ${CMAKE_CURRENT_BINARY_DIR}/image COPYONLY)
#configure_file(Lena.png ${CMAKE_CURRENT_BINARY_DIR}/image COPYONLY)

