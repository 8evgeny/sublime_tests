set(CMAKE_CXX_STANDARD 17)

project(test)
add_executable(${PROJECT_NAME}
    main.cpp
    parsing.cpp
    )

set (Boost_USE_MULTITHREADED ON)

find_package (Boost REQUIRED COMPONENTS
    thread
    system
    filesystem
    )

if (Boost_FOUND)
    message("cmake message-" ${PROJECT_NAME} " boost include DIR: " ${Boost_INCLUDE_DIR})
    include_directories (SYSTEM ${Boost_INCLUDE_DIR})
endif ()

target_link_libraries(
    ${PROJECT_NAME}
    ${Boost_LIBRARIES}
    )
