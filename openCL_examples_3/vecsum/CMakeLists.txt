file(GLOB src main.cpp)

add_executable(vecsum ${src})
target_link_libraries(vecsum
    ${OpenCL_LIBRARY}
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    )
configure_file(vecsum.cl ${CMAKE_CURRENT_BINARY_DIR}/vecsum.cl COPYONLY)


