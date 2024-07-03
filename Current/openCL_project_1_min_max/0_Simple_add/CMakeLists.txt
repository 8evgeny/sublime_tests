file(GLOB src
    main.cpp
    )

add_executable(0_Simple_add ${src})
target_link_libraries(0_Simple_add
    ${OpenCL_LIBRARY}
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    ${OpenCV_LIBS}
    )
#configure_file(edges.cl ${CMAKE_CURRENT_BINARY_DIR}/edges.cl COPYONLY)
#configure_file(matches.cl ${CMAKE_CURRENT_BINARY_DIR}/matches.cl COPYONLY)

