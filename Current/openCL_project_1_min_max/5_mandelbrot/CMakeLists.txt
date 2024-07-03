add_executable(5_mandelbrot main.cpp)
target_link_libraries(5_mandelbrot
    ${OpenCL_LIBRARY}
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    ${OpenCV_LIBS}
    )
configure_file(mandelbrot.cl ${CMAKE_CURRENT_BINARY_DIR}/mandelbrot.cl COPYONLY)



