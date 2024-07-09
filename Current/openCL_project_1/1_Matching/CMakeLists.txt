file(GLOB src
    main.cpp
    matchesOpenCv.cpp
    matchesCpuGpu.cpp
    )

add_executable(1_matching ${src})
target_link_libraries(1_matching
    ${OpenCL_LIBRARY}
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    ${OpenCV_LIBS}
    )
configure_file(matching.cl ${CMAKE_CURRENT_BINARY_DIR}/kernel COPYONLY)

#configure_file(tank_90.png ${CMAKE_CURRENT_BINARY_DIR}/image COPYONLY)
#configure_file(tankTemplate_90.png ${CMAKE_CURRENT_BINARY_DIR}/template COPYONLY)

configure_file(building.jpg ${CMAKE_CURRENT_BINARY_DIR}/image COPYONLY)
configure_file(buildingTemplate.jpg ${CMAKE_CURRENT_BINARY_DIR}/template COPYONLY)


