set(CMAKE_CXX_STANDARD 17)
   

ADD_EXECUTABLE(09_05_slist_and_pool main.cpp  )

 target_link_libraries(09_05_slist_and_pool
    PUBLIC libpqxx
    PUBLIC boost_thread
    PUBLIC boost_system
    Qt5::Core
    Qt5::Widgets
        # CONFIG
        )



