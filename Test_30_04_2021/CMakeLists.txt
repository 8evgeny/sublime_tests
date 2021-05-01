cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 14)
project(test_radar)
file(GLOB sources src/*)
add_executable(${PROJECT_NAME} ${sources})

set (Boost_USE_MULTITHREADED ON)
find_package (Boost REQUIRED COMPONENTS system filesystem )
if (Boost_FOUND)
    message("cmake message-" ${PROJECT_NAME} " boost include DIR: " ${Boost_INCLUDE_DIR})
    include_directories (SYSTEM ${Boost_INCLUDE_DIR})
endif ()

find_package( OpenCV REQUIRED )

message(STATUS "OpenCV library status:")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")
message(STATUS "     path: ${OpenCV_INSTALL_PATH}")

include_directories(${OpenCV_INCLUDE_DIRS})

target_include_directories(${PROJECT_NAME}
    PUBLIC
    include/
    ${OpenCV_INCLUDE_DIRS}
    )
target_link_libraries( ${PROJECT_NAME}
        ${Boost_LIBRARIES}
        ${OpenCV_LIBS}
        pthread
        )


