set(CMAKE_CXX_STANDARD 14)
project(test_radar)

add_executable(${PROJECT_NAME}
    ${PROJECT_NAME}.cpp
    )

set (Boost_USE_MULTITHREADED ON)

find_package (Boost REQUIRED COMPONENTS system filesystem )
if (Boost_FOUND)
    message("cmake message-" ${PROJECT_NAME} " boost include DIR: " ${Boost_INCLUDE_DIR})
    include_directories (SYSTEM ${Boost_INCLUDE_DIR})
endif ()

target_link_libraries(
    ${PROJECT_NAME}
    ${Boost_LIBRARIES}
    pthread
    )
