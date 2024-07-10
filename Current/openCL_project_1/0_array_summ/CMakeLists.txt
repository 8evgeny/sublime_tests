file(GLOB src
    main.cpp
    )

add_executable(0_array_summ ${src})
target_link_libraries(0_array_summ
    ${OpenCL_LIBRARY}
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    ${OpenCV_LIBS}
    )
configure_file(array_summ.cl ${CMAKE_CURRENT_BINARY_DIR}/kernel COPYONLY)


