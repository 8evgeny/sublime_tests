#set(classes_DIR "/home/xaviernx/QtProg/shared_memory/jetson_multimedia_api/samples/common/classes")
set(classes_DIR "/home/user/QtProg/shared_memory/jetson_multimedia_api/samples/common/classes")
set(lib_DIR "/usr/lib/aarch64-linux-gnu/tegra")

set(src_unitest
    camera_unit_sample.cpp
    camera_unit_sample.hpp
    camera_unit_sample_ctrls.cpp
    camera_unit_sample_ctrls.hpp
    camera_unit_sample_parser.cpp )
add_executable(${PROJECT_NAME}_camera_unit
    ${src_unitest}
    ${classes_DIR}/NvEglRenderer.cpp
    ${classes_DIR}/NvLogging.cpp
    ${classes_DIR}/NvEglRenderer.cpp
    ${classes_DIR}/NvElement.cpp
    ${classes_DIR}/NvElementProfiler.cpp )
target_include_directories(${PROJECT_NAME}_camera_unit PRIVATE
    samples/unittest_samples/camera_unit_sample )

target_link_libraries(${PROJECT_NAME}_camera_unit
    ${lib_DIR}/libnvv4l2.so
    ${lib_DIR}/libnvbufsurface.so
    pthread
    EGL
    GLESv2
    X11
    drm
    cuda
    vulkan
    )

