set(CMAKE_CXX_STANDARD 17)

    project(06_06_nonblocking_barrier)
    ADD_EXECUTABLE(${PROJECT_NAME} main.cpp )

    set (Boost_NO_SYSTEM_PATHS ON)
    set (Boost_USE_MULTITHREADED ON)
    set (Boost_USE_STATIC_LIBS ON)
    set (Boost_USE_STATIC_RUNTIME OFF)
    set (BOOST_ALL_DYN_LINK OFF)

    find_package (Boost REQUIRED COMPONENTS  thread system filesystem)

    if (Boost_FOUND)
        message(${Boost_INCLUDE_DIR})
        include_directories (SYSTEM ${Boost_INCLUDE_DIR})
    endif ()

    target_link_libraries(
        ${PROJECT_NAME}
        ${Boost_LIBRARIES}
        )

