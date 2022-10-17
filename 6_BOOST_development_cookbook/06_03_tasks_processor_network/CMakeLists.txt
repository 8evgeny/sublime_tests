    set(CMAKE_CXX_STANDARD 17)

    project(06_03_tasks_processor_network)

    file(GLOB src
        *
        ../06_01_tasks_processor_base/tasks_processor_base.hpp
        )

    ADD_EXECUTABLE(${PROJECT_NAME} ${src})
    set(BOOST_ROOT "/home/evg/boost/boost_1_80_0")
    set (Boost_NO_SYSTEM_PATHS ON)
    set (Boost_USE_MULTITHREADED ON)
    set (Boost_USE_STATIC_LIBS ON)
    set (Boost_USE_STATIC_RUNTIME OFF)
    set (BOOST_ALL_DYN_LINK OFF)

set (BOOST_INCLUDEDIR "/home/evg/boost")
set (BOOST_LIBRARYDIR "/home/evg/boost/boost_1_80_0/stage/lib")


    find_package (Boost REQUIRED COMPONENTS
        thread
        system
        )

    if (Boost_FOUND)
        message("cmake message-" ${PROJECT_NAME} " boost include DIR: " ${Boost_INCLUDE_DIR})
        include_directories (SYSTEM ${Boost_INCLUDE_DIR})
    endif ()



    target_link_libraries(
        ${PROJECT_NAME}
        ${Boost_LIBRARIES}
        )

