set(CMAKE_CXX_STANDARD 17)

project(Other_CompositeBuffersScatterInput)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(src CompositeBuffersScatterInput.cpp)

ADD_EXECUTABLE(${PROJECT_NAME} ${src})

target_link_libraries(${PROJECT_NAME}
/home/jhon/boost/boost_1_75_0/stage/lib/libboost_system.so
/home/jhon/boost/boost_1_75_0/stage/lib/libboost_thread.so
/usr/lib/libpthread.so
    )
   





