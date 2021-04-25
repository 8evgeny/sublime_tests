set(CMAKE_CXX_STANDARD 17)

project(datetime)
add_executable(${PROJECT_NAME}1 datetime1.cpp )

set(BOOST_ROOT "/home/jhon/boost/boost_1_75_0")
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


#target_link_libraries(${PROJECT_NAME}2  ${Boost_LIBRARIES} )
#target_link_libraries(${PROJECT_NAME}3  ${Boost_LIBRARIES} )
#target_link_libraries(${PROJECT_NAME}4  ${Boost_LIBRARIES} )
#target_link_libraries(${PROJECT_NAME}5  ${Boost_LIBRARIES} )
#target_link_libraries(${PROJECT_NAME}6  ${Boost_LIBRARIES} )
#target_link_libraries(${PROJECT_NAME}7  ${Boost_LIBRARIES} )
#target_link_libraries(${PROJECT_NAME}8  ${Boost_LIBRARIES} )
#target_link_libraries(${PROJECT_NAME}9  ${Boost_LIBRARIES} )
#target_link_libraries(${PROJECT_NAME}10  ${Boost_LIBRARIES} )
