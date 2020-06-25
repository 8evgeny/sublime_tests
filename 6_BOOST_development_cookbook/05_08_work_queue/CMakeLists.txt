set(CMAKE_CXX_STANDARD 17)
   

ADD_EXECUTABLE(05_08_work_queue main.cpp  )

 target_link_libraries(05_08_work_queue
    PUBLIC libpqxx
    PUBLIC boost_thread
    PUBLIC boost_system
    Qt5::Core
    Qt5::Widgets
        # CONFIG
        )



