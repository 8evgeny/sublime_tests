file(GLOB src
    main.cpp
    )

add_executable(0_add_vectors ${src})
target_link_libraries(0_add_vectors
    ${OpenCL_LIBRARY}
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    ${OpenCV_LIBS}
    )
configure_file(add_vectors.cl ${CMAKE_CURRENT_BINARY_DIR}/kernel COPYONLY)


