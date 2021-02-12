set(CMAKE_CXX_STANDARD 17)

project(test)
ADD_EXECUTABLE(${PROJECT_NAME}
    main.cpp
    parsingfiles.cpp
    )

set (Boost_USE_MULTITHREADED ON)

find_package (Boost REQUIRED COMPONENTS
    program_options
    regex
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
