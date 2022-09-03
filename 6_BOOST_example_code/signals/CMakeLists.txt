set(CMAKE_CXX_STANDARD 17)

project(signals)
add_executable(${PROJECT_NAME}1 signals1.cpp )
add_executable(${PROJECT_NAME}2 signals2.cpp )
add_executable(${PROJECT_NAME}3 signals3.cpp )
add_executable(${PROJECT_NAME}4 signals4.cpp )
add_executable(${PROJECT_NAME}5 signals5.cpp )
add_executable(${PROJECT_NAME}6 signals6.cpp )
add_executable(${PROJECT_NAME}7 signals7.cpp )
add_executable(${PROJECT_NAME}8 signals8.cpp )
add_executable(${PROJECT_NAME}9 signals9.cpp )
add_executable(${PROJECT_NAME}10 signals10.cpp )

set(BOOST_ROOT "/home/evg/boost/boost_1_80_0")
find_package (Boost REQUIRED COMPONENTS  thread system filesystem)
if (Boost_FOUND)
    message("cmake message-" ${PROJECT_NAME} " boost include DIR: " ${Boost_INCLUDE_DIR})
    include_directories (SYSTEM ${Boost_INCLUDE_DIR})
endif ()
set (Boost_NO_SYSTEM_PATHS ON)
set (Boost_USE_MULTITHREADED ON)
set (Boost_USE_STATIC_LIBS ON)
set (Boost_USE_STATIC_RUNTIME OFF)
set (BOOST_ALL_DYN_LINK OFF)

target_link_libraries(
    ${PROJECT_NAME}1
#    /usr/lib/libboost_thread.so
#    /usr/lib/libboost_system.so
#    /usr/lib/libpthread.so
    ${Boost_LIBRARIES}
    )

target_link_libraries(${PROJECT_NAME}2  ${Boost_LIBRARIES} )
target_link_libraries(${PROJECT_NAME}3  ${Boost_LIBRARIES} )
target_link_libraries(${PROJECT_NAME}4  ${Boost_LIBRARIES} )
target_link_libraries(${PROJECT_NAME}5  ${Boost_LIBRARIES} )
target_link_libraries(${PROJECT_NAME}6  ${Boost_LIBRARIES} )
target_link_libraries(${PROJECT_NAME}7  ${Boost_LIBRARIES} )
target_link_libraries(${PROJECT_NAME}8  ${Boost_LIBRARIES} )
target_link_libraries(${PROJECT_NAME}9  ${Boost_LIBRARIES} )
target_link_libraries(${PROJECT_NAME}10  ${Boost_LIBRARIES} )
