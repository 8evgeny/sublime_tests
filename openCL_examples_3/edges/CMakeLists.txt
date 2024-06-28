file(GLOB src main.cpp)

add_executable(edges ${src})
target_link_libraries(edges
    ${OpenCL_LIBRARY}
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    )
configure_file(edges.cl ${CMAKE_CURRENT_BINARY_DIR}/edges.cl COPYONLY)
configure_file(image.jpg ${CMAKE_CURRENT_BINARY_DIR}/image.jpg COPYONLY)

