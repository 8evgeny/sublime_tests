file(GLOB src
    image_filtering.cpp
    )

add_executable(image_filtering ${src})
target_link_libraries(image_filtering
    ${OpenCL_LIBRARY}
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    ${OpenCV_LIBS}
    -lm -lpthread -lX11
    )
configure_file(image_filtering.cl ${CMAKE_CURRENT_BINARY_DIR}/image_filtering.cl COPYONLY)
configure_file(input_img.jpg ${CMAKE_CURRENT_BINARY_DIR}/input_img.jpg COPYONLY)



