cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 14)
project(test_rtsp_server)
set(OpenCV_DIR $ENV{HOME}/opencv/install_4_7_0_contrib)
add_executable(${PROJECT_NAME}_pipe main.cpp)
add_executable(${PROJECT_NAME} test-launch.c)

find_package(OpenCV REQUIRED PATHS ${OpenCV_DIR} NO_DEFAULT_PATH)
find_package(PkgConfig REQUIRED)
pkg_search_module(GSTREAMER REQUIRED gstreamer-1.0)
pkg_search_module(GSTREAMER_APP REQUIRED gstreamer-app-1.0)


include_directories(
    ${OpenCV_INCLUDE_DIRS}
    )
target_include_directories(${PROJECT_NAME} PRIVATE
    ${GSTREAMER_INCLUDE_DIRS}
    ${GSTREAMER_APP_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME}
    ${GSTREAMER_LDFLAGS}
    ${GSTREAMER_APP_LDFLAGS}
)


target_link_libraries( ${PROJECT_NAME}_pipe  ${OpenCV_LIBS} )
