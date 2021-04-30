cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 14)

project(test_radar)
file(GLOB sources src/*)
add_executable(${PROJECT_NAME} ${sources})

#set(OpenCV_DIR ${THIRD_PARTY_INSTALL_DIR}/lib/cmake/opencv4 CACHE PATH "")

set (Boost_USE_MULTITHREADED ON)
find_package (Boost REQUIRED COMPONENTS system filesystem )
if (Boost_FOUND)
    message("cmake message-" ${PROJECT_NAME} " boost include DIR: " ${Boost_INCLUDE_DIR})
    include_directories (SYSTEM ${Boost_INCLUDE_DIR})
endif ()

#find_package(OpenCV REQUIRED PATHS ${OpenCV_DIR} NO_DEFAULT_PATH)
find_package(OpenCV REQUIRED )
target_include_directories(${PROJECT_NAME} PUBLIC include/ )
target_link_libraries( ${PROJECT_NAME}
        ${Boost_LIBRARIES}
        ${OpenCV_LIBS}
        pthread
        )
