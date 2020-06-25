set(CMAKE_CXX_STANDARD 17)
   

ADD_EXECUTABLE(06_02_tasks_processor_timers main.cpp  )

 target_link_libraries(06_02_tasks_processor_timers
    PUBLIC libpqxx
    PUBLIC boost_thread
    PUBLIC boost_system
    Qt5::Core
    Qt5::Widgets
        # CONFIG
        )



