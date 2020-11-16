set(CMAKE_CXX_STANDARD 17)
project(05_01_atomics)
ADD_EXECUTABLE(${PROJECT_NAME} main.cpp  )

#find_package(Boost COMPONENTS boost_thread  REQUIRED)
#if(NOT Boost_FOUND)
#        message(SEND_ERROR "Failed to find boost::boost_thread.")
#        return()
#else()
#        include_directories(${Boost_INCLUDE_DIRS})
#endif()


target_link_libraries(
    ${PROJECT_NAME}
    /usr/lib/libboost_thread.so
    /usr/lib/libboost_system.so
    /usr/lib/libpthread.so
#    ${Boost}
    )




