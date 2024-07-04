file(GLOB src
    matching.cpp
    )

add_executable(2_matching ${src})
target_link_libraries(2_matching
    ${OpenCL_LIBRARY}
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    ${OpenCV_LIBS}
    )
configure_file(Lab4.cl ${CMAKE_CURRENT_BINARY_DIR}/kernel COPYONLY)
#configure_file(Lab4_1.cl ${CMAKE_CURRENT_BINARY_DIR}/kernel COPYONLY)

#configure_file(colaImage.jpg ${CMAKE_CURRENT_BINARY_DIR}/image COPYONLY)
#configure_file(colaTemplate.jpg ${CMAKE_CURRENT_BINARY_DIR}/template COPYONLY)

#configure_file(building.jpg ${CMAKE_CURRENT_BINARY_DIR}/image COPYONLY)
#configure_file(buildingTemplate.jpg ${CMAKE_CURRENT_BINARY_DIR}/template COPYONLY)

configure_file(tank.png ${CMAKE_CURRENT_BINARY_DIR}/image COPYONLY)
configure_file(tankTemplate.png ${CMAKE_CURRENT_BINARY_DIR}/template COPYONLY)
