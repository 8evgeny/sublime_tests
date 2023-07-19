cmake_minimum_required(VERSION 3.15)
project(POCO_test)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a")

add_subdirectory(timer)
add_subdirectory(server)
add_subdirectory(md5)
add_subdirectory(Any_Type)
add_subdirectory(DynamicAny_Type)

add_subdirectory(Timestamp)


#add_subdirectory(Foundation)
#add_subdirectory(XML)
#add_subdirectory(Util)
#add_subdirectory(Net)
#add_subdirectory(NetSSL)
#add_subdirectory(Data)

