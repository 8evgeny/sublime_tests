set(CMAKE_CXX_STANDARD 17)
   

ADD_EXECUTABLE(06_08_tasks_processor_signals main.cpp  )

 target_link_libraries(06_08_tasks_processor_signals
    PUBLIC libpqxx
    PUBLIC boost_thread
    PUBLIC boost_system
    Qt5::Core
    Qt5::Widgets
        # CONFIG
        )



