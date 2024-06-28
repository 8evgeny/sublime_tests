set(CLASS_DIR ${CMAKE_SOURCE_DIR}/common/classes)
set(lib_DIR "/usr/lib/aarch64-linux-gnu/tegra")
include_directories(/usr/include/drm)
set(ARGUS_UTILS_DIR "${CMAKE_SOURCE_DIR}/../argus/samples/utils")

#add_definitions(-DWRITE_TO_FILE_ON)

set(src_utils
    ${ARGUS_UTILS_DIR}/Thread.cpp
    ${ARGUS_UTILS_DIR}/NativeBuffer.cpp
    ${ARGUS_UTILS_DIR}/nvmmapi/NvNativeBuffer.cpp  )
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
    ${CLASS_DIR}/NvVulkanRenderer.cpp  )
add_executable(${PROJECT_NAME}_10_argus_camera_recording
    ${CMAKE_SOURCE_DIR}/10_argus_camera_recording/10_sample_camera_recording.cpp
    ${src_utils}
    ${src_classes} )
target_include_directories(${PROJECT_NAME}_10_argus_camera_recording PUBLIC  ${ARGUS_UTILS_DIR} )
target_link_libraries(${PROJECT_NAME}_10_argus_camera_recording
    pthread
    EGL
    GLESv2
    X11
    drm
    cuda
    vulkan
    ${lib_DIR}/libnvargus_socketclient.so
    ${lib_DIR}/libnvv4l2.so
    ${lib_DIR}/libnvbufsurface.so
    ${lib_DIR}/libnvbufsurftransform.so )

#    /usr/local/cuda-11.4/targets/aarch64-linux/lib/libcudart.so
#    ${lib_DIR}/libnvosd.so
#    ${lib_DIR}/libnvjpeg.so
#    ${lib_CLASSES}




