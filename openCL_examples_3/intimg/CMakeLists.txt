file(GLOB src main.cpp)

add_executable(intimg ${src})
target_link_libraries(intimg
    ${OpenCL_LIBRARY}
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    )
configure_file(intimg.cl ${CMAKE_CURRENT_BINARY_DIR}/intimg.cl COPYONLY)
configure_file(image.jpg ${CMAKE_CURRENT_BINARY_DIR}/image.jpg COPYONLY)


