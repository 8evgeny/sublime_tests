cmake_minimum_required(VERSION 3.10)

project(inference)

set(OpenCV_DIR $ENV{HOME}/opencv/install_4_7_0_contrib)

find_package(OpenCV REQUIRED PATHS ${OpenCV_DIR} NO_DEFAULT_PATH)
include_directories(${OpenCV_DIR})

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/ 3rdparty.out)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/utils/ utils.out)

file(GLOB SRCS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc)
add_executable(${PROJECT_NAME} ${SRCS} )

target_link_libraries(${PROJECT_NAME}
    imageutils
    fileutils
    imagedrawing    
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/librknnrt.so
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/librga.so
    dl
    ${OpenCV_LIBS}
)
    set(THREADS_PREFER_PTHREAD_FLAG ON)
    find_package(Threads REQUIRED)
    target_link_libraries(${PROJECT_NAME} Threads::Threads)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/rknpu2/include
    ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/opencv/opencv-linux-aarch64/include/opencv2
)

file(COPY model DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY test_img/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
