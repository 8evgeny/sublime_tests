cmake_minimum_required (VERSION 2.6)

project(Samples)
include_directories(${CMAKE_SOURCE_DIR}/../include)

add_subdirectory(unittest_samples/camera_unit_sample)
add_subdirectory(09_argus_camera_jpeg)
add_subdirectory(10_argus_camera_recording)




