set(CMAKE_CXX_STANDARD 17)
   

ADD_EXECUTABLE(06_01_tasks_processor_base main.cpp  tasks_processor_base.hpp)

target_link_libraries(06_01_tasks_processor_base
    /usr/lib/libboost_thread.so
    /usr/lib/libboost_system.so
    /usr/lib/libpthread.so
#    ${Boost}
    )



