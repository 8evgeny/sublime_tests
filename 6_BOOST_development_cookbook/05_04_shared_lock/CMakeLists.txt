set(CMAKE_CXX_STANDARD 17)
   

ADD_EXECUTABLE(05_04_shared_lock main.cpp  )

 target_link_libraries(05_04_shared_lock
    PUBLIC libpqxx
    PUBLIC boost_thread
    PUBLIC boost_system
    Qt5::Core
    Qt5::Widgets
        # CONFIG
        )



