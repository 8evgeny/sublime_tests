file(GLOB src
    main.cpp
    edges.cpp
    workSerialEdges.cpp
    workParallelEdges.cpp
    )

add_executable(3_edges ${src})
target_link_libraries(3_edges
    ${OpenCL_LIBRARY}
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    ${OpenCV_LIBS}
    )
configure_file(edges.cl ${CMAKE_CURRENT_BINARY_DIR}/edges.cl COPYONLY)
configure_file(building.jpg ${CMAKE_CURRENT_BINARY_DIR}/image COPYONLY)


