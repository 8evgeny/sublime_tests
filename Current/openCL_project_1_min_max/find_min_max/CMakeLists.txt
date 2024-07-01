file(GLOB src find_min_max.cpp)

add_executable(${PROJECT_NAME} ${src})
target_link_libraries(${PROJECT_NAME}
    ${OpenCL_LIBRARY}
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    )
configure_file(find_min_max.cl ${CMAKE_CURRENT_BINARY_DIR}/find_min_max.cl COPYONLY)
#configure_file(tank_1.png ${CMAKE_CURRENT_BINARY_DIR}/imageIn COPYONLY)
configure_file(image.jpg ${CMAKE_CURRENT_BINARY_DIR}/image.jpg COPYONLY)
#configure_file(tank_2.png ${CMAKE_CURRENT_BINARY_DIR}/imageTmpl COPYONLY)
