set(CLASS_DIR ${CMAKE_SOURCE_DIR}/common/classes)
set(lib_DIR "/usr/lib/aarch64-linux-gnu/tegra")
set(ARGUS_UTILS_DIR "${CMAKE_SOURCE_DIR}/../argus/samples/utils")
include_directories(/usr/include/drm)

#add_definitions(-DJPEG_ON) # if JPEG_ON (in CMake building error, only make )
add_definitions(-DINFINITE_CAPTURE) # ignored CAPTURE_TIME
add_definitions(-DPREVIEW_ON) # ignored PREVIEW

set(src_classes
    ${CLASS_DIR}/NvEglRenderer.cpp
    ${CLASS_DIR}/NvLogging.cpp
    ${CLASS_DIR}/NvEglRenderer.cpp
    ${CLASS_DIR}/NvElement.cpp
    ${CLASS_DIR}/NvElementProfiler.cpp
    ${CLASS_DIR}/NvApplicationProfiler.cpp
    ${CLASS_DIR}/NvBuffer.cpp
    ${CLASS_DIR}/NvBufSurface.cpp
    ${CLASS_DIR}/NvDrmRenderer.cpp
#    ${CLASS_DIR}/NvJpegDecoder.cpp
#    ${CLASS_DIR}/NvJpegEncoder.cpp
    ${CLASS_DIR}/NvUtils.cpp
    ${CLASS_DIR}/NvV4l2Element.cpp
    ${CLASS_DIR}/NvV4l2ElementPlane.cpp
    ${CLASS_DIR}/NvVideoDecoder.cpp
    ${CLASS_DIR}/NvVideoEncoder.cpp
    ${CLASS_DIR}/NvVulkanRenderer.cpp )

#add_library(lib_CLASSES ${src_classes})

add_executable(${PROJECT_NAME}_09_argus_camera_jpeg
    ${CMAKE_SOURCE_DIR}/09_argus_camera_jpeg/09_argus_camera_jpeg.cpp
    ${ARGUS_UTILS_DIR}/Thread.cpp
    ${src_classes} )

target_include_directories(${PROJECT_NAME}_09_argus_camera_jpeg PRIVATE
    ${ARGUS_UTILS_DIR} )

target_link_libraries(${PROJECT_NAME}_09_argus_camera_jpeg
    ${lib_DIR}/libnvv4l2.so
    ${lib_DIR}/libnvbufsurface.so
    pthread
    EGL
    GLESv2
    X11
    drm
    cuda
    vulkan
    /usr/lib/aarch64-linux-gnu/tegra/libnvargus_socketclient.so
    ${lib_DIR}/libnvbufsurftransform.so
    /usr/local/cuda-11.4/targets/aarch64-linux/lib/libcudart.so
    ${lib_DIR}/libnvosd.so
    ${lib_DIR}/libnvjpeg.so )
#    ${lib_CLASSES}
