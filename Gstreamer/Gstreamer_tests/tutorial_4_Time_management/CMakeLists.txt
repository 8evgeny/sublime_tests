cmake_minimum_required(VERSION 3.10)
project(tutorial_4_Time_management)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GSTREAMER REQUIRED gstreamer-1.0)

include_directories(${GSTREAMER_INCLUDE_DIRS})
link_directories(${GSTREAMER_LIBRARY_DIRS})

add_executable(${PROJECT_NAME} basic-tutorial-4.c)
target_link_libraries(${PROJECT_NAME} ${GSTREAMER_LIBRARIES})
