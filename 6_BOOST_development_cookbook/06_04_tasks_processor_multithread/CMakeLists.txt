set(CMAKE_CXX_STANDARD 17)
   

    project(06_04_tasks_processor_multithread)
    ADD_EXECUTABLE(${PROJECT_NAME} main.cpp tasks_processor_multithread.hpp )

    set(BOOST_ROOT "/home/evg/boost/boost_1_80_0")
    set (Boost_NO_SYSTEM_PATHS ON)
    set (Boost_USE_MULTITHREADED ON)
    set (Boost_USE_STATIC_LIBS ON)
    set (Boost_USE_STATIC_RUNTIME OFF)
    set (BOOST_ALL_DYN_LINK OFF)

    find_package (Boost REQUIRED COMPONENTS  thread system filesystem)
#    find_package(Boost COMPONENTS *boost libraries here*)
    if (Boost_FOUND)
        message(${Boost_INCLUDE_DIR})
        include_directories (SYSTEM ${Boost_INCLUDE_DIR})

    endif ()

    target_link_libraries(
        ${PROJECT_NAME}
        ${Boost_LIBRARIES}
        )

#    set(Boost_USE_STATIC_LIBS OFF)
#    set(Boost_USE_MULTITHREADED ON)
#    set(Boost_USE_STATIC_RUNTIME OFF)
#    find_package(Boost 1.45.0 COMPONENTS *boost libraries here*)

#    if(Boost_FOUND)
#        include_directories(${Boost_INCLUDE_DIRS})
#        add_executable(progname file1.cxx file2.cxx)
#        target_link_libraries(progname ${Boost_LIBRARIES})
#    endif()
