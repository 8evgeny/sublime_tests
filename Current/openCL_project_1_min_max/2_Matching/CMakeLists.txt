file(GLOB src
    main.cpp
    )

add_executable(2_matching ${src})
target_link_libraries(2_matching
    ${OpenCL_LIBRARY}
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    ${OpenCV_LIBS}
    )
configure_file(Lab4.cl ${CMAKE_CURRENT_BINARY_DIR}/Lab4.cl COPYONLY)
configure_file(Lab4_1.cl ${CMAKE_CURRENT_BINARY_DIR}/Lab4_1.cl COPYONLY)
configure_file(baseImage.jpg ${CMAKE_CURRENT_BINARY_DIR}/baseImage.jpg COPYONLY)
configure_file(template.jpg ${CMAKE_CURRENT_BINARY_DIR}/template.jpg COPYONLY)
#configure_file(building.jpg ${CMAKE_CURRENT_BINARY_DIR}/baseImage.jpg COPYONLY)
#configure_file(buildingTemplate.jpg ${CMAKE_CURRENT_BINARY_DIR}/template.jpg COPYONLY)
