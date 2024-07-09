add_library(SobelFilter
    SobelFilter.cpp
    )

include_directories(CMAKE_CURRENT_BINARY_DIR}/../../3_edge2/common/FreeImage/include)
add_executable(3_edge2
    RunSobel.cpp
    SobelFilter
    libfreeimage.a
    )
target_link_libraries(3_edge2
    ${OpenCL_LIBRARY}
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    ${OpenCV_LIBS}
    )
configure_file(SobelFilter.cl ${CMAKE_CURRENT_BINARY_DIR}/kernel COPYONLY)

configure_file(Lena.png ${CMAKE_CURRENT_BINARY_DIR}/image COPYONLY)


