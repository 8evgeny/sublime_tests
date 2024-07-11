file(GLOB src
    reduction.cpp
    )

add_executable(9_reduction ${src})
target_link_libraries(9_reduction
    ${OpenCL_LIBRARY}
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    ${OpenCV_LIBS}
    )
configure_file(reduction.cl ${CMAKE_CURRENT_BINARY_DIR}/reduction.cl COPYONLY)




