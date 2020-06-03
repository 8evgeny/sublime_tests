set(CMAKE_CXX_STANDARD 17)
   

ADD_EXECUTABLE(09_01_hash main.cpp  )

 target_link_libraries(09_01_hash
    PUBLIC libpqxx
    PUBLIC boost_thread
    PUBLIC boost_system
    Qt5::Core
    Qt5::Widgets
        # CONFIG
        )



