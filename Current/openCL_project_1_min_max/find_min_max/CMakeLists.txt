file(GLOB src
    main.cpp
    workParallelEdges.cpp
    workSerialEdges.cpp
    edges.cpp
    workSerialMatches.cpp
    matches.cpp
    )

add_executable(${PROJECT_NAME} ${src})
target_link_libraries(${PROJECT_NAME}
    ${OpenCL_LIBRARY}
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    ${OpenCV_LIBS}
    )
configure_file(edges.cl ${CMAKE_CURRENT_BINARY_DIR}/edges.cl COPYONLY)

#configure_file(tank.png ${CMAKE_CURRENT_BINARY_DIR}/image COPYONLY)
#configure_file(tankTemplate.png ${CMAKE_CURRENT_BINARY_DIR}/template COPYONLY)

configure_file(building.jpg ${CMAKE_CURRENT_BINARY_DIR}/image COPYONLY)
configure_file(buildingTemplate.jpg ${CMAKE_CURRENT_BINARY_DIR}/template COPYONLY)

#configure_file(room.jpeg ${CMAKE_CURRENT_BINARY_DIR}/image COPYONLY)

