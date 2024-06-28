file(GLOB src main.cpp)

add_executable(parsum ${src})
target_link_libraries(parsum
    ${OpenCL_LIBRARY}
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    )
configure_file(parsum.cl ${CMAKE_CURRENT_BINARY_DIR}/parsum.cl COPYONLY)


