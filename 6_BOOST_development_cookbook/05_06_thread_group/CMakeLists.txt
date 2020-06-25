set(CMAKE_CXX_STANDARD 17)
   

ADD_EXECUTABLE(05_06_thread_group main.cpp  )

 target_link_libraries(05_06_thread_group
    PUBLIC libpqxx
    PUBLIC boost_thread
    PUBLIC boost_system
    Qt5::Core
    Qt5::Widgets
        # CONFIG
        )



