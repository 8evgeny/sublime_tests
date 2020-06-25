set(CMAKE_CXX_STANDARD 17)
   

ADD_EXECUTABLE(06_04_tasks_processor_multithread main.cpp  )

 target_link_libraries(06_04_tasks_processor_multithread
    PUBLIC libpqxx
    PUBLIC boost_thread
    PUBLIC boost_system
    Qt5::Core
    Qt5::Widgets
        # CONFIG
        )



