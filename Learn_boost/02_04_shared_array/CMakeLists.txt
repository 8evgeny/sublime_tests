set(CMAKE_CXX_STANDARD 17)
   

ADD_EXECUTABLE(02_04_shared_array main.cpp  )

 target_link_libraries(02_04_shared_array
    PUBLIC libpqxx
    PUBLIC boost_thread
    PUBLIC boost_system
    Qt5::Core
    Qt5::Widgets
        # CONFIG
        )



