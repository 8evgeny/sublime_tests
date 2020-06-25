set(CMAKE_CXX_STANDARD 17)
   

ADD_EXECUTABLE(06_03_tasks_processor_network main.cpp  )

 target_link_libraries(06_03_tasks_processor_network
    PUBLIC libpqxx
    PUBLIC boost_thread
    PUBLIC boost_system
    Qt5::Core
    Qt5::Widgets
        # CONFIG
        )



