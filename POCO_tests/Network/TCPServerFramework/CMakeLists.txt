cmake_minimum_required(VERSION 3.5)

project(Sockets)
set (name1 StreamSocket)
set (name2 ServerSocket)
set (name3 UDP_Socket_send)
set (name4 UDP_Socket_receive)
set (name5 MulticastSocket_receive)

include(${CMAKE_SOURCE_DIR}/Network/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(Network_${PROJECT_NAME}_${name1} ${name1}.cpp)
set_target_properties(Network_${PROJECT_NAME}_${name1} PROPERTIES CXX_STANDARD 20 CXX_STANDARD_REQUIRED ON COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra" )
target_link_libraries(Network_${PROJECT_NAME}_${name1} ${CONAN_LIBS} )

add_executable(Network_${PROJECT_NAME}_${name2} ${name2}.cpp)
set_target_properties(Network_${PROJECT_NAME}_${name2} PROPERTIES CXX_STANDARD 20 CXX_STANDARD_REQUIRED ON COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra" )
target_link_libraries(Network_${PROJECT_NAME}_${name2} ${CONAN_LIBS} )

add_executable(Network_${PROJECT_NAME}_${name3} ${name3}.cpp)
set_target_properties(Network_${PROJECT_NAME}_${name3} PROPERTIES CXX_STANDARD 20 CXX_STANDARD_REQUIRED ON COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra" )
target_link_libraries(Network_${PROJECT_NAME}_${name3} ${CONAN_LIBS} )

add_executable(Network_${PROJECT_NAME}_${name4} ${name4}.cpp)
set_target_properties(Network_${PROJECT_NAME}_${name4} PROPERTIES CXX_STANDARD 20 CXX_STANDARD_REQUIRED ON COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra" )
target_link_libraries(Network_${PROJECT_NAME}_${name4} ${CONAN_LIBS} )

add_executable(Network_${PROJECT_NAME}_${name5} ${name5}.cpp)
set_target_properties(Network_${PROJECT_NAME}_${name5} PROPERTIES CXX_STANDARD 20 CXX_STANDARD_REQUIRED ON COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra" )
target_link_libraries(Network_${PROJECT_NAME}_${name5} ${CONAN_LIBS} )
